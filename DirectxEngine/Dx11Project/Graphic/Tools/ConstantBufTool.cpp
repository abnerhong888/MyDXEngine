#include "ConstantBufTool.h"


bool DX11::ConstantBufTool::isInitialized = false;;
DX11::sptrDevice DX11::ConstantBufTool::mDevice;
DX11::sptrDevContext DX11::ConstantBufTool::mDevContext;

DX11::sptrConstBufData<Tex2D_ColorAlphaCB> DX11::ConstantBufTool::mTex2DColorAlphaConstBuf;
DX11::sptrConstBufData<Tex2D_ColorRatioAlphaCB> DX11::ConstantBufTool::mTex2DColorRatioAlphaConstBuf;

bool DX11::ConstantBufTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	mDevice = pDevice;
	isInitialized = true;
	BuffData l_BufData;
	//////////////////////////////////////////////////////////////////////////
	ZeroMemory(&l_BufData, sizeof(BuffData));
	l_BufData.Name = "Tex2D_ColorRatioAlphaCB ConstantBuffer";
	l_BufData.Desc.Usage = D3D11_USAGE_DEFAULT;
	l_BufData.Desc.ByteWidth = sizeof(Tex2D_ColorRatioAlphaCB);
	l_BufData.Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	l_BufData.Desc.CPUAccessFlags = 0;
	l_BufData.Desc.MiscFlags = 0;
	l_BufData.Initdata.pSysMem = nullptr;

	mTex2DColorRatioAlphaConstBuf = CreateConstantBuffer<Tex2D_ColorRatioAlphaCB>(l_BufData);
	if (mTex2DColorRatioAlphaConstBuf == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	ZeroMemory(&l_BufData, sizeof(BuffData));
	l_BufData.Name = "Tex2D_ColorAlphaCB ConstantBuffer";
	l_BufData.Desc.Usage = D3D11_USAGE_DEFAULT;
	l_BufData.Desc.ByteWidth = sizeof(Tex2D_ColorAlphaCB);
	l_BufData.Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	l_BufData.Desc.CPUAccessFlags = 0;
	l_BufData.Desc.MiscFlags = 0;
	l_BufData.Initdata.pSysMem = nullptr;

	mTex2DColorAlphaConstBuf = CreateConstantBuffer<Tex2D_ColorAlphaCB>(l_BufData);
	if (mTex2DColorAlphaConstBuf == nullptr) return false;
	return true;
}

ID3D11Buffer *DX11::ConstantBufTool::GetCBuffer(ConstantBufType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "ConstantBufTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::Tex2D_ColorAlpha_CB:
		return mTex2DColorAlphaConstBuf->GetConstantBuffer();
	case DX11::Tex2D_ColorRatioAlpha_CB:
		return mTex2DColorRatioAlphaConstBuf->GetConstantBuffer();
	case DX11::ConstantBufTotal:
	default:
		g_SysLog->Log(_ERROR, "Error GetCBuffer %d", static_cast<int>(type));
		return nullptr;
	}
}

void *DX11::ConstantBufTool::GetCBData(ConstantBufType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "ConstantBufTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::Tex2D_ColorAlpha_CB:
		return mTex2DColorAlphaConstBuf->GetData();
	case DX11::Tex2D_ColorRatioAlpha_CB:
		return mTex2DColorRatioAlphaConstBuf->GetData();
	case DX11::ConstantBufTotal:
	default:
		g_SysLog->Log(_ERROR, "Error GetCBData %d", static_cast<int>(type));
		return nullptr;
	}
}

void DX11::ConstantBufTool::SetConstantBuf(ConstantBufType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "ConstantBufTool is uninitialized");
		return;
	}
#endif

	ID3D11Buffer* l_ConstantBuffer = GetCBuffer(type);
	void *l_data = GetCBData(type);

	mDevContext->UpdateSubresource(l_ConstantBuffer, 0, NULL, l_data, 0, 0);
	mDevContext->VSSetConstantBuffers(0, 1, &l_ConstantBuffer);
	mDevContext->PSSetConstantBuffers(0, 1, &l_ConstantBuffer);
}
