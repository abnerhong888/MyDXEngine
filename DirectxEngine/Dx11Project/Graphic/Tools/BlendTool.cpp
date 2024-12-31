#include "BlendTool.h"

bool DX11::BlendTool::isInitialized = false;;
DX11::sptrDevContext DX11::BlendTool::mDevContext;
DX11::sptrDevice DX11::BlendTool::mDevice;
DX11::sptrBlend DX11::BlendTool::mAlphaBlend;
DX11::sptrBlend DX11::BlendTool::mAddBlend;
DX11::sptrBlend DX11::BlendTool::mFontBlend;
DX11::sptrBlend DX11::BlendTool::mDstZeroBlend;

bool DX11::BlendTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	mDevice = pDevice;
	isInitialized = true;
	
	D3D11_BLEND_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BLEND_DESC));
	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//////////////////////////////////////////////////////////////////////////
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	mAlphaBlend = CreateBlend("mAlphaBlend", Desc);
	if (mAlphaBlend == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	mAddBlend = CreateBlend("mAddBlend", Desc);
	if (mAddBlend == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	mFontBlend = CreateBlend("mFontBlend", Desc);
	if (mFontBlend == nullptr) return false;
	
	//////////////////////////////////////////////////////////////////////////
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_DEST_COLOR;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	mDstZeroBlend = CreateBlend("mDstZeroBlend", Desc);
	if (mDstZeroBlend == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////



	
	return true;
}

ID3D11BlendState *DX11::BlendTool::Get(BlendType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "BlendTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::AlphaBlend:
		return mAlphaBlend.get();
	case DX11::AddBlend:
		return mAddBlend.get();
	case DX11::FontBlend:
		return mFontBlend.get();
	case DX11::DstZeroBlend:
		return mDstZeroBlend.get();
	case DX11::NullState:
		return nullptr;
	case DX11::BlendTotal:
	default:
		g_SysLog->Log(_ERROR, "Error BlendType %d", static_cast<int>(type));
		return nullptr;
	}
}

void DX11::BlendTool::SetBlend(BlendType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "BlendTool is uninitialized");
		return;
	}
#endif
	mDevContext->OMSetBlendState(Get(type), 0, 0xffffffff);
}

void DX11::BlendTool::SetBlend(sptrBlend pBlend)
{
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "BlendTool is uninitialized");
		return;
	}
	mDevContext->OMSetBlendState(pBlend.get(), 0, 0xffffffff);
}

DX11::sptrBlend DX11::BlendTool::CreateBlend(std::string pName, D3D11_BLEND_DESC pDesc)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "BlendTool is uninitialized");
		return nullptr;
	}
#endif
	HRESULT hr = S_OK;
	ID3D11BlendState *l_blendstate = nullptr;

	auto CreateBlendLambda = [&](std::string name) ->bool
	{
		l_blendstate = nullptr;
		hr = mDevice->CreateBlendState(&pDesc, &l_blendstate);
		if (FAILED(hr))
		{
			std::string str = "CreateBlendState " + name + " is failed.";
			g_SysLog->Log(_ERROR, str.c_str());
			return false;
		}
		return true;
	};

	if (!CreateBlendLambda(pName)) return nullptr;
	return SmartPointer::CreateShared(l_blendstate);
}