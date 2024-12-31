#include "ShaderTool.h"
#include "D3Dcompiler.h"
#include "Typedefs\LayoutStruct.h"

#define Source_FX_Folder L"..//..//..//Dx11Project//shader//"
#define Compiled_Folder L".//shader//" //Working Direction


bool DX11::ShaderTool::isInitialized = false;;
DX11::sptrDevice DX11::ShaderTool::mDevice;
DX11::sptrDevContext DX11::ShaderTool::mDevContext;

DX11::sptrShaderData DX11::ShaderTool::mTex2D;
DX11::sptrShaderData DX11::ShaderTool::mTex2D_ColorAlpha;
DX11::sptrShaderData DX11::ShaderTool::mTex2D_ColorRatioAlpha;
DX11::sptrShaderData DX11::ShaderTool::mTex3D;

//////////////////////////////////////////////////////////////////////////

bool DX11::ShaderTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	mDevice = pDevice;
	isInitialized = true;

	ShaderModel l_ShaderModel = _shadermodel::g_ShaderModel_5_0;

	//////////////////////////////////////////////////////////////////////////

	mTex2D = CreateShader("mTex2D", L"Texture2D", g_Texture2DLayout, ARRAYSIZE(g_Texture2DLayout), l_ShaderModel);
	if (mTex2D == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	mTex2D_ColorAlpha = CreateShader("mTex2D_ColorAlpha", L"Texture2DColorAlpha", g_Texture2DLayout, ARRAYSIZE(g_Texture2DLayout), l_ShaderModel);
	if (mTex2D_ColorAlpha == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////

	mTex2D_ColorRatioAlpha = CreateShader("mTex2D_ColorRatioAlpha", L"Texture2DColorRatioAlpha", g_Texture2DLayout, ARRAYSIZE(g_Texture2DLayout), l_ShaderModel);
	if (mTex2D_ColorRatioAlpha == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////

	mTex3D = CreateShader("mTex3D", L"Texture3D", g_Texture3DLayout, ARRAYSIZE(g_Texture3DLayout), l_ShaderModel);
	if (mTex3D == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////


	return true;
}

DX11::ShaderData *DX11::ShaderTool::Get(ShaderTpye type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "ShaderTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::Tex2D:
		return mTex2D.get();
	case DX11::Tex2D_ColorAlpha:
		return mTex2D_ColorAlpha.get();
	case DX11::Tex2D_ColorRatioAlpha:
		return mTex2D_ColorRatioAlpha.get();
	case DX11::Tex3D:
		return mTex3D.get();
	case DX11::ShaderTotal:
	default:
		g_SysLog->Log(_ERROR, "Error ShaderTpye %d", static_cast<int>(type));
		return nullptr;
	}

}

void DX11::ShaderTool::SetShader(ShaderTpye type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "ShaderTool is uninitialized");
		return;
	}
#endif

	mDevContext->VSSetShader(Get(type)->GetVertexShader(), NULL, 0);
	mDevContext->PSSetShader(Get(type)->GetPixelShader(), NULL, 0);
	mDevContext->IASetInputLayout(Get(type)->GetInputLayout());

}

void DX11::ShaderTool::SetShader(sptrShaderData pShaderData)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "ShaderTool is uninitialized");
		return;
	}
#endif
	mDevContext->VSSetShader(pShaderData->GetVertexShader(), NULL, 0);
	mDevContext->PSSetShader(pShaderData->GetPixelShader(), NULL, 0);
	mDevContext->IASetInputLayout(pShaderData->GetInputLayout());
}

DX11::sptrShaderData DX11::ShaderTool::CreateShader(
	std::string pName, 
	std::wstring pShaderName, 
	D3D11_INPUT_ELEMENT_DESC *pLayout,
	UINT NumElements,
	ShaderModel pShaderModel)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "ShaderTool is uninitialized");
		return nullptr;
	}
#endif
	if (!FileSystem::isDirExist(L".//shader//")) // working direction
	{
		FileSystem::CreateDir(L".//shader//");
	}

	if (!CheckFeatureLevel(pShaderModel)) return nullptr;

	ShaderData *l_ShaderData = nullptr;
	//////////////////////////////////////////////////////////////////////////
	bool isSuccessed = DX11::ShaderCreator::_CreaterShader(
		mDevice,
		pLayout,
		NumElements,
		pShaderModel,
		pShaderName,
		&l_ShaderData
	);

	if (!isSuccessed)
	{
		std::string str = "CreateShader " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return nullptr;
	}
	
	return SmartPointer::CreateShared(l_ShaderData);
}

bool DX11::ShaderTool::CheckFeatureLevel(ShaderModel pShaderModel)
{
	D3D_FEATURE_LEVEL FeatureLevel = mDevice->GetFeatureLevel();

	D3D_FEATURE_LEVEL MyFeatureLevel;

	if (pShaderModel.VertexModel == "vs_5_1")
		MyFeatureLevel = D3D_FEATURE_LEVEL_11_1;
	else if (pShaderModel.VertexModel == "vs_5_0")
		MyFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	else if (pShaderModel.VertexModel == "vs_4_0")
		MyFeatureLevel = D3D_FEATURE_LEVEL_10_0;

	if (MyFeatureLevel > FeatureLevel)
	{
		std::string level;
		switch (FeatureLevel)
		{
		case D3D_FEATURE_LEVEL_9_1: level = "D3D_FEATURE_LEVEL_9_1"; break;
		case D3D_FEATURE_LEVEL_9_2: level = "D3D_FEATURE_LEVEL_9_2"; break;
		case D3D_FEATURE_LEVEL_9_3: level = "D3D_FEATURE_LEVEL_9_3"; break;
		case D3D_FEATURE_LEVEL_10_0:level = "D3D_FEATURE_LEVEL_10_0"; break;
		case D3D_FEATURE_LEVEL_10_1:level = "D3D_FEATURE_LEVEL_10_1"; break;
		case D3D_FEATURE_LEVEL_11_0:level = "D3D_FEATURE_LEVEL_11_0"; break;
		case D3D_FEATURE_LEVEL_11_1:level = "D3D_FEATURE_LEVEL_11_1"; break;
		default:					level = "Error level"; break;
		}
		g_SysLog->Log(_ERROR, "CheckFeatureLevel-> Your shader model version is to high !");
		g_SysLog->Log(_ERROR, "CheckFeatureLevel-> Current feature level is: %s", level.c_str());
	
		return false;
	}


	return true;
}

void DX11::ShaderTool::ClearCompliedShader()
{
	std::vector<std::wstring> vsList = FileSystem::getFilesName(Compiled_Folder, L"*.vs");
	if (vsList.size() != FileSystem::DeleteFiles(vsList))
	{
		g_SysLog->Log(_ERROR, "Delete *.vs Error.");
	}

	std::vector<std::wstring> psList = FileSystem::getFilesName(Compiled_Folder, L"*.ps");
	if (psList.size() != FileSystem::DeleteFiles(psList))
	{
		g_SysLog->Log(_ERROR, "Delete *.ps Error.");
	}

}
//////////////////////////////////////////////////////////////////////////

DX11::ShaderData::ShaderData(
	ID3D11VertexShader *pVshader,
	ID3D10Blob *pVbuffer,
	ID3D11PixelShader *pPshader,
	ID3D10Blob *pPbuffer,
	ID3D11InputLayout *pInputLauout,
	std::wstring pFileName)
{
	this->mVertexShader = pVshader;
	this->mVertexShaderBuffer = pVbuffer;
	this->mPixelShader = pPshader;
	this->mPixelShaderBuffer = pPbuffer;
	this->mInputLayout = pInputLauout;
	this->mFileName = pFileName;
}


ID3D11VertexShader *DX11::ShaderData::GetVertexShader() const
{
	return mVertexShader;
}

ID3D11PixelShader *DX11::ShaderData::GetPixelShader() const
{
	return mPixelShader;
}

ID3D11InputLayout *DX11::ShaderData::GetInputLayout() const
{
	return mInputLayout;
}

ID3D10Blob *DX11::ShaderData::GetPixelShaderBuffer() const
{
	return mPixelShaderBuffer;
}

ID3D10Blob *DX11::ShaderData::GetVertexShaderBuffer() const
{
	return mVertexShaderBuffer;
}

std::wstring DX11::ShaderData::GetShaderFileName() const
{
	return mFileName;
}

void DX11::ShaderData::Release()
{
	SAFE_RELEASE(mVertexShader);
	SAFE_RELEASE(mPixelShader);
	SAFE_RELEASE(mVertexShaderBuffer);
	SAFE_RELEASE(mPixelShaderBuffer);
	SAFE_RELEASE(mInputLayout);
}

//////////////////////////////////////////////////////////////////////////
std::shared_ptr<ErrorLogger> DX11::ShaderCreator::mShaderLogger;
DX11::sptrDevice DX11::ShaderCreator::mDevice;
DX11::ShaderData *DX11::ShaderCreator::mShaderData;
DX11::ShaderModel *DX11::ShaderCreator::mShaderModel;
std::wstring DX11::ShaderCreator::mFileName;


bool DX11::ShaderCreator::_CreaterShader(
	sptrDevice pDevice,
	D3D11_INPUT_ELEMENT_DESC *Layout,
	UINT NumElements,
	ShaderModel pModel,
	std::wstring pShaderName,
	ShaderData **pShaderData
)
{
	if (!mDevice) { mDevice = pDevice; }
	if (!mShaderLogger)
	{
		std::string l_path = StringConverter::WideToString(Compiled_Folder) + "//Log//";
		mShaderLogger = SmartPointer::CreateShared(new ErrorLogger(l_path, "shaderLog"));
		mShaderLogger->LogFileShouldBeDelete(1);
	}

	mShaderData = nullptr;
	mShaderModel = &pModel;
	shdata shData = { 0 };
	shData.Layout = Layout;
	shData.NumLayouts = NumElements;
	
	//////////////////////////////////////////////////////////////////////////
	
	mFileName = Source_FX_Folder + pShaderName + L".fx";
	bool isFXExist = FileSystem::isFileExit(mFileName);

	if (isFXExist) // source folder
	{
		if (!FXShaderCompiler(shData)) return false;
		if (!SaveToBinaryFile(shData, pShaderName)) return false;
	}
	else
	{
		mFileName = Compiled_Folder + pShaderName + L".fx";
		isFXExist = FileSystem::isFileExit(mFileName);
		if (isFXExist) //fx
		{
			if (!FXShaderCompiler(shData)) return false;
			if (!SaveToBinaryFile(shData, pShaderName)) return false;
		}
		else //vs ps
		{
			mFileName = Compiled_Folder + pShaderName;
			if (!LoadShaderBinFile(shData)) return false;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	mShaderData = new ShaderData(
		shData.VShader,
		shData.VBuffer,
		shData.PShader,
		shData.PBuffer,
		shData.InputLayout,
		mFileName
	);
	*pShaderData = mShaderData;
	return true;
}
bool DX11::ShaderCreator::SaveToBinaryFile(shdata &pshdata, std::wstring pFileName)
{
	std::fstream fs;
	std::string l_FileName;
	std::string str;

	auto l_FileWrite = [&](ID3D10Blob *Buffer) ->bool
	{
		
		fs.open(l_FileName.c_str(), std::ifstream::out | std::ifstream::binary | std::ifstream::trunc);

		if (!fs.good())
		{
			str = "CreateFile : " + l_FileName + " is failed.";
			g_SysLog->Log(_ERROR, str.c_str());
			return false;
		}
		fs.write(
			reinterpret_cast<char*>(Buffer->GetBufferPointer()),
			Buffer->GetBufferSize()
		);
		fs.close();
		return true;
	};
	
	//////////////////////////////////////////////////////////////////////////
	l_FileName = StringConverter::WideToString(Compiled_Folder + pFileName) + ".vs";
	if (!l_FileWrite(pshdata.VBuffer)) return false;

	str = l_FileName + "   |-----Write File Great ! -----|\n";
	mShaderLogger->Log(_INFO, str.c_str());


	l_FileName = StringConverter::WideToString(Compiled_Folder + pFileName) + ".ps";
	if (!l_FileWrite(pshdata.PBuffer)) return false;

	str = l_FileName + "   |-----Write File Great ! -----|\n";
	mShaderLogger->Log(_INFO, str.c_str());
	

	return true;

}

bool DX11::ShaderCreator::LoadShaderBinFile(shdata &pshdata)
{
	HRESULT hr = S_OK;
	std::ifstream stream;
	size_t size;
	char *data = nullptr;
	std::string l_FileName;
	l_FileName = StringConverter::WideToString(mFileName) + ".vs";
	auto l_Checker = [&](std::string name)
	{
		if (FAILED(hr))
		{
			std::string str = " " + l_FileName + " is failed.";
			g_SysLog->Log(_ERROR, str.c_str());
			return false;
		}
		return true;
	};
	auto l_CheckOpen = [&]()
	{
		stream.open(l_FileName.c_str(), std::ifstream::in | std::ifstream::binary);
		if (!stream.good())
		{
			std::string str = "Open " + l_FileName + " is failed.";
			g_SysLog->Log(_ERROR, str.c_str());
			return false;
		}

		stream.seekg(0, std::ios::end);
		size = size_t(stream.tellg());
		data = (char*)malloc(sizeof(char) * size);
		stream.seekg(0, std::ios::beg);
		stream.read(data, size);
		stream.close();
		return true;
	};
	//////////////////////////////////////////////////////////////////////////
	l_FileName = StringConverter::WideToString(mFileName) + ".vs";

	if (!l_CheckOpen()) return false;
	
	hr = mDevice->CreateVertexShader(
		data, 
		size, 
		NULL, 
		&pshdata.VShader);

	if (!l_Checker("CreateVertexShader")) return false;

	hr = mDevice->CreateInputLayout(
		pshdata.Layout,
		pshdata.NumLayouts,
		data,
		size,
		&pshdata.InputLayout); 

	if (data)
	{
		free(data); data = nullptr;
	}
	if (!l_Checker("CreateInputLayout")) return false;

	
	//////////////////////////////////////////////////////////////////////////
	l_FileName = StringConverter::WideToString(mFileName) + ".ps";

	if (!l_CheckOpen()) return false;

	hr = mDevice->CreatePixelShader(
		data, 
		size, 
		NULL, 
		&pshdata.PShader);

	
	if (data)
	{
		free(data); data = nullptr;
	}
	if (!l_Checker("CreatePixelShader")) return false;

	
	std::string str = StringConverter::WideToString(mFileName) + ".vs .ps   |-----Load Great ! -----|\n";
	mShaderLogger->Log(_INFO, str.c_str());

	return true;
}

bool DX11::ShaderCreator::FXShaderCompiler(shdata &pshdata)
{
	mShaderLogger->Log(_INFO, "--------------------------------------------------------------------");
	if (!CompilerShaderFile(pshdata, "Vertex"))
	{
		std::string str = "CompilerShaderFile Vertex is Failed. : " + StringConverter::WideToString(mFileName);
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}
	if (!CompilerShaderFile(pshdata, "Pixel"))
	{
		std::string str = "CompilerShaderFile Pixel is Failed. : " + StringConverter::WideToString(mFileName);
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}
	if (!Create(pshdata)) return false;

	
	std::string str = StringConverter::WideToString(mFileName) + "   |-----Compiler Great ! -----|\n";
	mShaderLogger->Log(_INFO, str.c_str());
	return true;
}

bool DX11::ShaderCreator::CompilerShaderFile(shdata &pshdata, std::string Type)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;


#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	const D3D_SHADER_MACRO defines[] =
	{
		//"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	LPCSTR l_Entry = nullptr;
	LPCSTR l_Model = nullptr;
	ID3DBlob *buff = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	if (Type == "Vertex")
	{
		l_Entry = mShaderModel->VertexEntryPoint.c_str();
		l_Model = mShaderModel->VertexModel.c_str();
	}
	else if (Type == "Pixel")
	{
		l_Entry = mShaderModel->PixelEntryPoint.c_str();
		l_Model = mShaderModel->PixelModel.c_str();
	}
	
	hr = D3DCompileFromFile(
		mFileName.c_str(), 
		defines, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		l_Entry, 
		l_Model,
		dwShaderFlags, 
		0, 
		&buff, 
		&pErrorBlob);

	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
		{
			mShaderLogger->Log(_ERROR, (char*)pErrorBlob->GetBufferPointer());
		}
		else
		{
			mShaderLogger->LogHRESULT(_ERROR, GetLastError(), StringConverter::WideToString(mFileName) + " D3DX11CompileFromFile VertexShader");
		}
		SAFE_RELEASE(pErrorBlob);
		return false;
	}
	SAFE_RELEASE(pErrorBlob);

	if (Type == "Vertex")
	{
		 pshdata.VBuffer = buff;
	}
	else if (Type == "Pixel")
	{
		pshdata.PBuffer = buff;
	}

	return true;
}

bool DX11::ShaderCreator::Create(shdata &pshdata)
{
	HRESULT hr = S_OK;
	auto l_Checker = [&](std::string name)
	{
		if (FAILED(hr))
		{
			std::string str = " " + StringConverter::WideToString(mFileName) + " is failed.";
			g_SysLog->Log(_ERROR, str.c_str());
			return false;
		}
		return true;
	};
	//////////////////////////////////////////////////////////////////////////
	hr = mDevice->CreateVertexShader(
		pshdata.VBuffer->GetBufferPointer(),
		pshdata.VBuffer->GetBufferSize(),
		NULL,
		&pshdata.VShader);

	if (!l_Checker("CreateVertexShader")) return false;


	hr = mDevice->CreateInputLayout(
		pshdata.Layout,
		pshdata.NumLayouts,
		pshdata.VBuffer->GetBufferPointer(),
		pshdata.VBuffer->GetBufferSize(),
		&pshdata.InputLayout);

	if (!l_Checker("CreateInputLayout")) return false;

	hr = mDevice->CreatePixelShader(
		pshdata.PBuffer->GetBufferPointer(),
		pshdata.PBuffer->GetBufferSize(),
		NULL,
		&pshdata.PShader);

	if (!l_Checker("CreatePixelShader")) return false;

	return true;

}





