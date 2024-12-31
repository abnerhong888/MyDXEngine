#include "RenderTargetViewTool.h"

bool					DX11::RTVTool::isInitialized = false;;
DX11::sptrDevice		DX11::RTVTool::mDevice;
DX11::sptrDevContext	DX11::RTVTool::mDevContext;

DX11::sptrRTVData		DX11::RTVTool::mOutView;

bool DX11::RTVTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext, int pDisplayTexW, int pDisplayTexH)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	isInitialized = true;

	mOutView = CreateRTV("mOutView", pDisplayTexW, pDisplayTexH, RENDER_SRV_TARGET, RGBA8_U);
	if (mOutView == nullptr) return false;


	return true;
}

DX11::RTVData *DX11::RTVTool::Get(RTVType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RenderTargetViewTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::OutView:
		return mOutView.get();
	case DX11::RTVTotal:
	default:
		g_SysLog->Log(_ERROR, "Error RTVData %d", static_cast<int>(type));
		return nullptr;
		
	}
}

DX11::sptrRTVData DX11::RTVTool::GetSptr(RTVType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RenderTargetViewTool is uninitialized");
		return nullptr;
	}
#endif

	switch (type)
	{
	case DX11::OutView:
		return mOutView;
	case DX11::RTVTotal:
	default:
		g_SysLog->Log(_ERROR, "Error RTVData %d", static_cast<int>(type));
		return nullptr;

	}
}

void DX11::RTVTool::SetRenderTargetView(RTVType pRTVType, bool pClean, ColorType pColor)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RenderTargetViewTool is uninitialized");
		return;
	}
#endif

	ID3D11RenderTargetView *l_targetView = Get(pRTVType)->GetRTView();
	mDevContext->OMSetRenderTargets(1, &l_targetView, NULL);
	if (pClean)
	{
		MT::float3 *l_color = Color::Get(pColor);
		float l_cc[4] = { l_color->r, l_color->g, l_color->b, 0.0 };
		
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}
}

void DX11::RTVTool::SetRenderTargetView(sptrRTVData pRTVData, bool pClean, ColorType pColor)
{
	ID3D11RenderTargetView *l_targetView = pRTVData->GetRTView();
	mDevContext->OMSetRenderTargets(1, &l_targetView, NULL);
	if (pClean)
	{
		MT::float3 *l_color = Color::Get(pColor);
		float l_cc[4] = { l_color->r, l_color->g, l_color->b, 0.0 };
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}
}


DX11::sptrRTVData DX11::RTVTool::CreateRTV(std::string pName, int pTexW, int pTexH, TextureType pTexType, TextureFormat pTexFormat)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RenderTargetViewTool is uninitialized");
		return nullptr;
	}
#endif
	RTVData *l_RTVData = nullptr;

	ID3D11Resource				*l_Tex = nullptr;
	ID3D11ShaderResourceView	*l_SRV = nullptr;
	ID3D11RenderTargetView		*l_RTView = nullptr;
	bool isSuccess = true;

	//////////////////////////////////////////////////////////////////////////
	isSuccess &= TextureTool::CreateTexRGBA_2D(pName, pTexW, pTexH, pTexType, pTexFormat, &l_Tex);
	isSuccess &= TextureTool::CreateSRV_2D(pName, l_Tex, pTexFormat, &l_SRV);
	isSuccess &= TextureTool::CreateRTV_2D(pName, l_Tex, &l_RTView);
	if (!isSuccess)
	{
		return nullptr;
	}
	l_RTVData = new RTVData(l_RTView, l_SRV, l_Tex);

	return SmartPointer::CreateShared(l_RTVData);
}
//////////////////////////////////////////////////////////////////////////

DX11::RTVData::RTVData(
	ID3D11RenderTargetView		*pRTView,
	ID3D11ShaderResourceView	*pSRV,
	ID3D11Resource				*pTex
)
{
	this->mRenderTargetView		= pRTView;
	this->mShaderResourceView	= pSRV;
	this->mTexture				= pTex;
}

ID3D11RenderTargetView *DX11::RTVData::GetRTView()const
{
	return mRenderTargetView;
}

ID3D11ShaderResourceView *DX11::RTVData::GetSRV()const
{
	return mShaderResourceView;
}

ID3D11Resource	*DX11::RTVData::GetTex()const
{
	return mTexture;
}

void DX11::RTVData::Release()
{
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mShaderResourceView);
	SAFE_RELEASE(mTexture);
}
