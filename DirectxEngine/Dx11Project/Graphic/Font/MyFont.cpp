#include "MyFont.h"
#include <sstream>
#include <algorithm>

std::vector<int> StringSplitToInt(std::string str, char c);

static D3D11_INPUT_ELEMENT_DESC g_FontLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

DX11::MyFont::MyFont()
{

}

DX11::MyFont &DX11::MyFont::GetIns()
{
	static MyFont l_ins;
	return l_ins;
}

bool DX11::MyFont::Initialize(std::wstring pFontFile, sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevice = pDevice;
	mDevContext = pDevContext;

	mFontFile = pFontFile;

	if (!CreateShader(L"Font")) return false; 
	if (!CreateConstantBuffer()) return false;
	if (!LoadFontFile()) return false;
	isInitialized = true;
	return true;
}

void DX11::MyFont::DrawString(int pPosx, int pPosy, float pFontSize, ColorType pClrtype, const wchar_t *pFmt, ...)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "Font is uninitialized");
		return;
	}
#endif
	va_list ap;
	va_start(ap, pFmt);
	int bytes_written = vswprintf(mTexbuf, sizeof(mTexbuf), pFmt, ap);
	va_end(ap);


	RenderTool::SetVertexDataType(TriangleList);
	RenderTool::SetSampler(0, LinearBorder);
	RenderTool::SetShaderRV(0, mFontSRV);
	RenderTool::SetShader(mFontShader);
	RenderTool::SetMesh(PlaneMesh);
	
	RenderTool::SetBlend(FontBlend);
	//////////////////////////////////////////////////////////////////////////
	ID3D11Buffer* l_ConstantBuffer = mConstBuffer->GetConstantBuffer();
	Font_CB *l_data = mConstBuffer->GetData();

	D3D11_VIEWPORT l_vp = RenderTool::GetCurrentVP(1);
	
	l_data->posX = ((float)pPosx / l_vp.Width) * 2.0f - 1.0f;
	l_data->posY = -((float)pPosy / l_vp.Height) * 2.0f + 1.0f;

	MT::float3 *l_clr = Color::Get(pClrtype);
	l_data->colorR = l_clr->x;
	l_data->colorG = l_clr->y;
	l_data->colorB = l_clr->z;

	std::wstring l_str(mTexbuf);
	for (int i = 0; i < l_str.length();i++)
	{
		wordinfo info = mFontInfo.WordMap[l_str[i]];
		if (info.w == 0 || info.h == 0) { continue; }

		float l_fontRatio = info.w / info.h;
		l_data->fontX = info.x;
		l_data->fontY = info.y;
		l_data->fontW = info.w;
		l_data->fontH = info.h;
		l_data->scaleX = (pFontSize / l_vp.Width) * l_fontRatio;
		l_data->scaleY = (pFontSize / l_vp.Height);

		RenderTool::SetContantBuffer(mConstBuffer);
		RenderTool::MeshDraw(PlaneMesh, DrawIndices);
		l_data->posX += l_data->scaleX * 2.0f;
	}

	RenderTool::SetBlend(NullState);
	
}

void DX11::MyFont::DrawStringPush(int pPosx, int pPosy, float pFontSize, ColorType pClrtype, const wchar_t *pFmt, ...)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "Font is uninitialized");
		return;
	}
#endif

	va_list ap;
	va_start(ap, pFmt);
	int bytes_written = vswprintf(mTexbuf, sizeof(mTexbuf), pFmt, ap);
	va_end(ap);
	std::wstring l_str(mTexbuf);

	D3D11_VIEWPORT l_vp = RenderTool::GetCurrentVP(1);
	float l_posX = ((float)pPosx / l_vp.Width) * 2.0f - 1.0f;
	for (int i = 0; i < l_str.length(); i++)
	{
		wordinfo info = mFontInfo.WordMap[l_str[i]];
		if (info.w == 0 || info.h == 0) { continue; }

		float l_fontRatio = info.w / info.h;
		l_posX -= ((pFontSize / l_vp.Width) * l_fontRatio) * 2.0f;
	}

	float l_leftPos = (((l_posX / 2.0f) + 1.0f) / 2.0f) * l_vp.Width;

	DrawString(static_cast<int>(l_leftPos), pPosy, pFontSize, pClrtype, l_str.c_str());
}


DX11::FontInfo DX11::MyFont::GetFontInfo()
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "Font is uninitialized");
		return FontInfo();
	}
#endif
	return mFontInfo;
}

bool DX11::MyFont::LoadFontFile()
{
	std::ifstream fp;
	std::wstring folder;
	std::size_t found = 0;
	found = mFontFile.find_last_of(L"\\");
	if (found != std::string::npos)
	{
		folder = mFontFile.substr(0, found+1);
	}

	fp.open(mFontFile.c_str(), std::ios::in);
	std::vector<std::string> lines;
	if (fp.is_open())
	{
		std::string line;
		while (getline(fp, line))
		{
			lines.emplace_back(line);
		}
		fp.close();
	}
	else
	{
		std::string str = "Can't not find font file: " + StringConverter::WideToString(mFontFile);
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}
	mFontInfo.WordMap.clear();
	
	for (std::string str : lines)
	{
		if (str == "") { continue; }
		found = str.find(".bmp");
		if (found != std::string::npos)
		{
			mFontInfo.BmpName = str;
		}
		found = str.find_first_of("=");
		if (found != std::string::npos)
		{
			std::string name = str.substr(0, found);
			std::string value = str.substr(found+1, str.length());
			if (name == "ImageW") { mFontInfo.width = std::atoi(value.c_str()); }
			if (name == "ImageH") { mFontInfo.height = std::atoi(value.c_str()); }
			if (name == "FontSize") { mFontInfo.fontsize = std::atoi(value.c_str()); }
			if (name == "Face") { mFontInfo.Face = value; }
		}
		found = str.find_first_of(",");
		if (found != std::string::npos)
		{
			std::vector<int> list = StringSplitToInt(str, ',');
			mFontInfo.WordMap[static_cast<wchar_t>(list[0])] = 
				wordinfo(list[1] / (float)mFontInfo.width,
						list[2] / (float)mFontInfo.height,
						list[3] / (float)mFontInfo.width,
						list[4] / (float)mFontInfo.height);
		}
	}

	
	std::wstring finename = folder + std::wstring(mFontInfo.BmpName.begin(), mFontInfo.BmpName.end());
	mFontSRV = TextureTool::CreateSRVFromFile_2D(finename);
	return true;
}


bool DX11::MyFont::CreateShader(std::wstring pShaderName)
{
	mFontShader = ShaderTool::CreateShader("mFontShader", pShaderName, g_FontLayout, ARRAYSIZE(g_FontLayout), _shadermodel::g_ShaderModel_5_0);
	if (mFontShader == nullptr) return false;

	return true;
}

bool DX11::MyFont::CreateConstantBuffer()
{
	BuffData l_BufData;
	l_BufData.Name = "Font ConstantBuffer";
	l_BufData.Desc.Usage = D3D11_USAGE_DEFAULT;
	l_BufData.Desc.ByteWidth = sizeof(Font_CB);
	l_BufData.Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	l_BufData.Desc.CPUAccessFlags = 0;
	l_BufData.Desc.MiscFlags = 0;
	l_BufData.Initdata.pSysMem = nullptr;

	mConstBuffer = ConstantBufTool::CreateConstantBuffer<Font_CB>(l_BufData);
	if (mConstBuffer == nullptr) return false;

	return true;
}

std::vector<int> StringSplitToInt(std::string str, char c)
{
	std::string segment;
	std::vector<int> seglist;
	std::stringstream ss(str);

	while (std::getline(ss, segment, c))
	{
		seglist.push_back(atoi(segment.c_str()));
	}
	return seglist;
}