#include "TextureTool.h"

bool DX11::TextureTool::isInitialized = false;
DX11::sptrDevice DX11::TextureTool::mDevice;
DX11::sptrDevContext DX11::TextureTool::mDevContext;

bool DX11::TextureTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }
	mDevice = pDevice;
	mDevContext = pDevContext;

	isInitialized = true;
	return true;
}


bool DX11::TextureTool::CreateRTV_2D(std::string pName, ID3D11Resource *pTex, ID3D11RenderTargetView **pOutRTV)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	ID3D11RenderTargetView *l_RTV = nullptr;

	HRESULT hr = mDevice->CreateRenderTargetView(pTex, NULL, &l_RTV);
	if (FAILED(hr))
	{
		std::string str = "CreateRTV_2D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		*pOutRTV = nullptr;
		return false;
	}

	*pOutRTV = l_RTV;
	return true;
}

bool DX11::TextureTool::CreateSRV_2D(
	std::string pName, 
	ID3D11Resource *pTex,
	TextureFormat pFormat,
	ID3D11ShaderResourceView **pOutSRV)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	ID3D11ShaderResourceView *l_SRV = nullptr;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	srvDesc.Format = static_cast<DXGI_FORMAT>(pFormat);
	srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	HRESULT hr = mDevice->CreateShaderResourceView(pTex, &srvDesc, &l_SRV);

	if (FAILED(hr))
	{
		std::string str = "CreateSRV_2D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		*pOutSRV = nullptr;
		return false;
	}

	*pOutSRV = l_SRV;
	return true;
}

bool DX11::TextureTool::CreateTexRGBA_2D(
	std::string pName, int pWidth, int pHeight,
	TextureType pType,
	TextureFormat pFormat,
	ID3D11Resource **pOutTex)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	ID3D11Texture2D *l_Tex = nullptr;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	UINT l_BindFlag = 0;
	D3D11_USAGE l_Usage = D3D11_USAGE_DEFAULT;
	UINT l_CPUAccessFlag = 0;
	switch (pType)
	{
	case DX11::RENDER_SRV_TARGET:
		l_BindFlag = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		break;

	case DX11::CopyGPU2CPU:
		l_CPUAccessFlag |= D3D11_CPU_ACCESS_READ;
		l_Usage = D3D11_USAGE_STAGING; // (copy) from the GPU to the CPU.
		break;

	case DX11::SRV_GPU_R_CPU_W:
		l_CPUAccessFlag |= D3D11_CPU_ACCESS_WRITE;
		l_Usage = D3D11_USAGE_DYNAMIC; // GPU (read only) and the CPU (write only)
		l_BindFlag = D3D11_BIND_SHADER_RESOURCE;
		break;

	case DX11::TexTypeDefault:
		l_BindFlag = D3D11_BIND_SHADER_RESOURCE;
		break;
	}
	desc.Format = static_cast<DXGI_FORMAT>(pFormat);
	desc.Usage = l_Usage;
	desc.CPUAccessFlags = l_CPUAccessFlag;


	desc.BindFlags = l_BindFlag;
	desc.Width = pWidth;
	desc.Height = pHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;

	HRESULT hr = mDevice->CreateTexture2D(&desc, NULL, &l_Tex);

	if (FAILED(hr))
	{
		std::string str = "CreateTexRGBA_2D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		*pOutTex = nullptr;
		return false;
	}

	*pOutTex = l_Tex;
	return true;
}

DX11::sptrTexSRV DX11::TextureTool::CreateSRVFromFile_2D(std::wstring pFileName)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return nullptr;
	}
#endif
	TexSRV *l_TexSRV = new TexSRV();
	HRESULT hr = CreateWICTextureFromFile(mDevice.get(), pFileName.c_str(), &l_TexSRV->Resource, &l_TexSRV->SRV);
	
	if (FAILED(hr))
	{
		std::string str = StringConverter::WideToString(L"CreateSRVFromFile_2D " + pFileName + L" is failed.");
		g_SysLog->LogHRESULT(_ERROR, hr, str.c_str());
		return nullptr;
	}

	return SmartPointer::CreateShared(l_TexSRV);
}

DX11::sptrTexSRV DX11::TextureTool::CreateTexRGBASRV_2D(std::string pName, int pWidth, int pHeight, TextureType pType, TextureFormat pTexFormat)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return nullptr;
	}
#endif
	TexSRV *l_TexSRV = nullptr;

	ID3D11Resource				*l_Tex = nullptr;
	ID3D11ShaderResourceView	*l_SRV = nullptr;
	bool isSuccess = true;
	std::string l_name = "CreateTexRGBASRV_2D -> " + pName;

	isSuccess &= CreateTexRGBA_2D(l_name, pWidth, pHeight, pType, pTexFormat, &l_Tex);
	isSuccess &= CreateSRV_2D(pName, l_Tex, pTexFormat, &l_SRV);
	if (!isSuccess)
	{
		return nullptr;
	}
	l_TexSRV = new TexSRV(l_SRV, l_Tex);

	return SmartPointer::CreateShared(l_TexSRV);
}

bool DX11::TextureTool::CopyTexToCPU_2D(std::string pName, ID3D11Resource *pTex, BYTE *CpuMem)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	D3D11_TEXTURE2D_DESC Desc;
	reinterpret_cast<ID3D11Texture2D*>(pTex)->GetDesc(&Desc);
	
	if (CpuMem == nullptr)
	{
		std::string str = "CopyTexToCPU_2D " + pName + " CpuMem is nullptr.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	if(Desc.CPUAccessFlags != D3D11_CPU_ACCESS_READ)
	{
		std::string str = "CopyTexToCPU_2D " + pName + " is not Access Read.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	if (Desc.Usage != D3D11_USAGE_STAGING)
	{
		std::string str = "CopyTexToCPU_2D " + pName + " is not Usage Staging.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = mDevContext->Map(pTex, 0, D3D11_MAP_READ, 0, &mappedResource);

	if (mappedResource.pData == nullptr)
	{
		std::string str = "CopyTexToCPU_2D " + pName + " map data is null.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}
	 
	if (hr != S_OK)
	{
		std::string str = "CopyTexToCPU_2D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	BYTE *src = (BYTE *)mappedResource.pData;
	BYTE *dst = (BYTE *)CpuMem;
	int FormatSize = GetFotmatByteSize(Desc.Format);

	for (int y = 0; y < static_cast<int>(Desc.Height); y++) 
	{
		memcpy(dst, src, Desc.Width * FormatSize);
		src += mappedResource.RowPitch;
		dst += Desc.Width * FormatSize;
	}

	mDevContext->Unmap(pTex, 0);
	return true;
}

void DX11::TextureTool::CopyTexToTex_2D(ID3D11Resource *pSrcTex, ID3D11Resource *pDstTex)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return;
	}
#endif
	mDevContext->CopyResource(pDstTex, pSrcTex);
}

void DX11::TextureTool::CopyTexAreaToTex_2D(ID3D11Resource *pSrcTex, ID3D11Resource *pDstTex,
	D3D11_BOX pBox, int pDstX, int pDstY, int pDstZ)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return;
	}
#endif
	mDevContext->CopySubresourceRegion(pDstTex, 0, pDstX, pDstY, pDstZ, pSrcTex, 0, &pBox);
}

bool DX11::TextureTool::UpdateTex_2D(std::string pName, ID3D11Resource *pTex, void *pData, int pDataW, int pDataH, TextureFormat pFormat)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	D3D11_TEXTURE2D_DESC Desc;
	reinterpret_cast<ID3D11Texture2D*>(pTex)->GetDesc(&Desc);

	if (Desc.CPUAccessFlags != D3D11_CPU_ACCESS_WRITE)
	{
		std::string str = "UpdateTex_2D " + pName + " is not Access Write.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	if (Desc.Usage != D3D11_USAGE_DYNAMIC)
	{
		std::string str = "UpdateTex_2D " + pName + " is not DYNAMIC.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT l_hr = mDevContext->Map(pTex, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	BYTE *dst = (BYTE *)mappedResource.pData;
	BYTE *src = (BYTE *)pData;

	int l_FormatSize = GetFotmatByteSize(static_cast<DXGI_FORMAT>(pFormat));

	if (pFormat != Desc.Format)
	{
		std::string str = "UpdateTex_2D " + pName + " Format is different.";
		g_SysLog->Log(_ERROR, str.c_str());
		mDevContext->Unmap(pTex, 0);
		return false;
	}

	for (int y = 0; y < pDataH; y++) 
	{
		memcpy(dst, src, pDataW * l_FormatSize);
		dst += mappedResource.RowPitch;
		src += pDataW * l_FormatSize;
	}

	mDevContext->Unmap(pTex, 0);
	return true;
}
//////////////////////////////////////////////////////////////////////////

DX11::sptrTexSRV DX11::TextureTool::CreateSRVFromFile_3D(std::wstring pFileName)
{
	return CreateSRVFromFile_2D(pFileName);
}

bool DX11::TextureTool::CreateRTV_3D(std::string pName, ID3D11Resource *pTex, ID3D11RenderTargetView **pOutRTV)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	ID3D11RenderTargetView *l_RTV = nullptr;

	HRESULT hr = mDevice->CreateRenderTargetView(pTex, NULL, &l_RTV);
	if (FAILED(hr))
	{
		std::string str = "CreateRTV_3D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		*pOutRTV = nullptr;
		return false;
	}

	*pOutRTV = l_RTV;
	return true;
}

bool DX11::TextureTool::CreateSRV_3D(
	std::string pName,
	ID3D11Resource *pTex,
	TextureFormat pFormat,
	ID3D11ShaderResourceView **pOutSRV)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	ID3D11ShaderResourceView *l_SRV = nullptr;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	srvDesc.Format = static_cast<DXGI_FORMAT>(pFormat);
	srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE3D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	HRESULT hr = mDevice->CreateShaderResourceView(pTex, &srvDesc, &l_SRV);

	if (FAILED(hr))
	{
		std::string str = "CreateSRV_3D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		*pOutSRV = nullptr;
		return false;
	}

	*pOutSRV = l_SRV;
	return true;
}

bool DX11::TextureTool::CreateTexRGBA_3D(
	std::string pName, int pWidth, int pHeight, int pDepth,
	TextureType pType,
	TextureFormat pFormat,
	ID3D11Resource **pOutTex)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	ID3D11Texture3D *l_Tex = nullptr;

	D3D11_TEXTURE3D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE3D_DESC));

	UINT l_BindFlag = 0;
	D3D11_USAGE l_Usage = D3D11_USAGE_DEFAULT;
	UINT l_CPUAccessFlag = 0;
	switch (pType)
	{
	case DX11::RENDER_SRV_TARGET:
		l_BindFlag = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		break;

	case DX11::CopyGPU2CPU:
		l_CPUAccessFlag |= D3D11_CPU_ACCESS_READ;
		l_Usage = D3D11_USAGE_STAGING; // (copy) from the GPU to the CPU.
		break;

	case DX11::SRV_GPU_R_CPU_W:
		l_CPUAccessFlag |= D3D11_CPU_ACCESS_WRITE;
		l_Usage = D3D11_USAGE_DYNAMIC; // GPU (read only) and the CPU (write only)
		l_BindFlag = D3D11_BIND_SHADER_RESOURCE;
		break;

	case DX11::TexTypeDefault:
		l_BindFlag = D3D11_BIND_SHADER_RESOURCE;
		break;
	}
	desc.Format = static_cast<DXGI_FORMAT>(pFormat);
	desc.Usage = l_Usage;
	desc.CPUAccessFlags = l_CPUAccessFlag;


	desc.BindFlags = l_BindFlag;
	desc.Width = pWidth;
	desc.Height = pHeight;
	desc.Depth = pDepth;
	desc.MipLevels = 1;
	
	HRESULT hr = mDevice->CreateTexture3D(&desc, NULL, &l_Tex);

	if (FAILED(hr))
	{
		std::string str = "CreateTexRGBA_3D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		*pOutTex = nullptr;
		return false;
	}

	*pOutTex = l_Tex;
	return true;
}

bool DX11::TextureTool::CopyTexToCPU_3D(std::string pName, ID3D11Resource *pTex, BYTE *CpuMem)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	D3D11_TEXTURE3D_DESC Desc;
	reinterpret_cast<ID3D11Texture3D*>(pTex)->GetDesc(&Desc);

	if (CpuMem == nullptr)
	{
		std::string str = "CopyTexToCPU_3D " + pName + " CpuMem is nullptr.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	if (Desc.CPUAccessFlags != D3D11_CPU_ACCESS_READ)
	{
		std::string str = "CopyTexToCPU_3D " + pName + " is not Access Read.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	if (Desc.Usage != D3D11_USAGE_STAGING)
	{
		std::string str = "CopyTexToCPU_3D " + pName + " is not Usage Staging.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = mDevContext->Map(pTex, 0, D3D11_MAP_READ, 0, &mappedResource);

	if (mappedResource.pData == nullptr)
	{
		std::string str = "CopyTexToCPU_3D " + pName + " map data is null.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	if (hr != S_OK)
	{
		std::string str = "CopyTexToCPU_3D " + pName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	BYTE *src = (BYTE *)mappedResource.pData;
	BYTE *dst = (BYTE *)CpuMem;
	int FormatSize = GetFotmatByteSize(Desc.Format);

	for (int z = 0; z < static_cast<int>(Desc.Depth); z++)
	{
		for (int y = 0; y < static_cast<int>(Desc.Height); y++)
		{
			memcpy(dst, src, Desc.Width * FormatSize);
			src += mappedResource.RowPitch;
			dst += Desc.Width * FormatSize;
		}
	}
	mDevContext->Unmap(pTex, 0);
	return true;
}

void DX11::TextureTool::CopyTexToTex_3D(ID3D11Resource *pSrcTex, ID3D11Resource *pDstTex)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return;
	}
#endif
	mDevContext->CopyResource(pDstTex, pSrcTex);
}

bool DX11::TextureTool::UpdateTex_3D(std::string pName, ID3D11Resource *pTex, void *pData, int pDataW, int pDataH, int pDataD, TextureFormat pFormat)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "TextureTool is uninitialized");
		return false;
	}
#endif
	D3D11_TEXTURE3D_DESC Desc;
	reinterpret_cast<ID3D11Texture3D*>(pTex)->GetDesc(&Desc);

	if (Desc.CPUAccessFlags != D3D11_CPU_ACCESS_WRITE)
	{
		std::string str = "UpdateTex_3D " + pName + " is not Access Write.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	if (Desc.Usage != D3D11_USAGE_DYNAMIC)
	{
		std::string str = "UpdateTex_3D " + pName + " is not DYNAMIC.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT l_hr = mDevContext->Map(pTex, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	BYTE *dst = (BYTE *)mappedResource.pData;
	BYTE *src = (BYTE *)pData;

	int l_FormatSize = GetFotmatByteSize(static_cast<DXGI_FORMAT>(pFormat));

	if (pFormat != Desc.Format)
	{
		std::string str = "UpdateTex_3D " + pName + " Format is different.";
		g_SysLog->Log(_ERROR, str.c_str());
		mDevContext->Unmap(pTex, 0);
		return false;
	}
	for (int z = 0; z < pDataD; z++)
	{
		for (int y = 0; y < pDataH; y++)
		{
			memcpy(dst, src, pDataW * l_FormatSize);
			dst += mappedResource.RowPitch;
			src += pDataW * l_FormatSize;
		}
	}
	
	mDevContext->Unmap(pTex, 0);
	return true;
}
// protected
int DX11::TextureTool::GetFotmatByteSize(DXGI_FORMAT pFormat)
{
	switch (pFormat)
	{
	case DXGI_FORMAT_R8_UNORM: return 1;
	case DXGI_FORMAT_R16_UNORM: return 2;
	case DXGI_FORMAT_R8G8B8A8_UNORM: return 4; 
	case DXGI_FORMAT_R16G16B16A16_UNORM: return 8;

	default: return 0;
	}
}