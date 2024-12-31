#include "RasterizerTool.h"

bool DX11::RasterizerTool::isInitialized = false;;

DX11::sptrDevContext DX11::RasterizerTool::mDevContext;
DX11::sptrDevice DX11::RasterizerTool::mDevice;
DX11::sptrRasterizer DX11::RasterizerTool::mSolid_Back;
DX11::sptrRasterizer DX11::RasterizerTool::mSolid_None;
DX11::sptrRasterizer DX11::RasterizerTool::mWire_Back;
DX11::sptrRasterizer DX11::RasterizerTool::mWire_None;

bool DX11::RasterizerTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{	
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	mDevice = pDevice;
	isInitialized = true;

	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.FrontCounterClockwise = FALSE;
	desc.DepthBias = 0;
	desc.SlopeScaledDepthBias = 0.0f;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = TRUE;
	desc.ScissorEnable = FALSE;
	desc.MultisampleEnable = FALSE;
	desc.AntialiasedLineEnable = FALSE;

	
	//////////////////////////////////////////////////////////////////////////
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;

	mSolid_Back = CreateRasterizer("mSolid_Back", desc);
	if (mSolid_Back == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_NONE;

	mSolid_None = CreateRasterizer("mSolid_None", desc);
	if (mSolid_None == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////

	desc.FillMode = D3D11_FILL_WIREFRAME;
	desc.CullMode = D3D11_CULL_BACK;

	mWire_Back = CreateRasterizer("mWire_Back", desc);
	if (mWire_Back == nullptr) return false;
	
	//////////////////////////////////////////////////////////////////////////

	desc.FillMode = D3D11_FILL_WIREFRAME;
	desc.CullMode = D3D11_CULL_NONE;

	mWire_None = CreateRasterizer("mWire_None", desc);
	if (mWire_None == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	
	return true;
}


ID3D11RasterizerState *DX11::RasterizerTool::Get(RasterizerType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RasterizerTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::Solid_Back:
		return mSolid_Back.get();
	case DX11::Solid_None:
		return mSolid_None.get();
	case DX11::Wire_Back:
		return mWire_Back.get();
	case DX11::Wire_None:
		return mWire_None.get();
	case DX11::RasterizerTotal:
	default:
		g_SysLog->Log(_ERROR, "Error RasterizerType %d", static_cast<int>(type));
		return nullptr;
	}
}

void DX11::RasterizerTool::SetRasterizer(RasterizerType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RasterizerTool is uninitialized");
		return;
	}
#endif
	mDevContext->RSSetState(Get(type));
}

void DX11::RasterizerTool::SetRasterizer(sptrRasterizer pRasterizer)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RasterizerTool is uninitialized");
		return;
	}
#endif
	mDevContext->RSSetState(pRasterizer.get());
}

DX11::sptrRasterizer DX11::RasterizerTool::CreateRasterizer(std::string pName, D3D11_RASTERIZER_DESC pDesc)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "RasterizerTool is uninitialized");
		return nullptr;
	}
#endif
	HRESULT hr;
	ID3D11RasterizerState* l_RasterizerState;

	auto CreateRasterizerLambda = [&](std::string name) ->bool
	{
		l_RasterizerState = nullptr;
		hr = mDevice->CreateRasterizerState(&pDesc, &l_RasterizerState);
		if (FAILED(hr))
		{
			std::string str = "CreateRasterizerState " + name + " is failed.";
			g_SysLog->Log(_ERROR, str.c_str());
			return false;
		}
		return true;
	};

	if (!CreateRasterizerLambda(pName)) return nullptr;
	return SmartPointer::CreateShared(l_RasterizerState);
}