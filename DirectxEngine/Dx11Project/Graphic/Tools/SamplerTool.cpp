#include "SamplerTool.h"

bool DX11::SamplerTool::isInitialized = false;;

DX11::sptrDevice		DX11::SamplerTool::mDevice;
DX11::sptrDevContext DX11::SamplerTool::mDevContext;

DX11::sptrSampler DX11::SamplerTool::mLinearWarp;
DX11::sptrSampler DX11::SamplerTool::mLinearMirror;
DX11::sptrSampler DX11::SamplerTool::mLinearClamp;
DX11::sptrSampler DX11::SamplerTool::mLinearBorder;

DX11::sptrSampler DX11::SamplerTool::mPointWarp;
DX11::sptrSampler DX11::SamplerTool::mPointMirror;
DX11::sptrSampler DX11::SamplerTool::mPointClamp;
DX11::sptrSampler DX11::SamplerTool::mPointBorder;


bool DX11::SamplerTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	mDevice = pDevice;
	isInitialized = true;

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	mLinearWarp = CreateSampler("mLinearWarp", sampDesc);
	if (mLinearWarp == nullptr) return false;
	
	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;

	mLinearMirror = CreateSampler("mLinearMirror", sampDesc);
	if (mLinearMirror == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	mLinearClamp = CreateSampler("mLinearClamp", sampDesc);
	if (mLinearClamp == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;

	mLinearBorder = CreateSampler("mLinearBorder", sampDesc);
	if (mLinearBorder == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	mPointWarp = CreateSampler("mPointWarp", sampDesc);
	if (mPointWarp == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;

	mPointMirror = CreateSampler("mPointMirror", sampDesc);
	if (mPointMirror == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	mPointClamp = CreateSampler("mPointClamp", sampDesc);
	if (mPointClamp == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;

	mPointBorder = CreateSampler("mPointBorder", sampDesc);
	if (mPointBorder == nullptr) return false;


	return true;
}

ID3D11SamplerState *DX11::SamplerTool::Get(SamplerType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "SamplerTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::LinearWarp:
		return mLinearWarp.get();
	case DX11::LinearMirror:
		return mLinearMirror.get();
	case DX11::LinearClamp:
		return mLinearClamp.get();
	case DX11::LinearBorder:
		return mLinearBorder.get();
	case DX11::PointWarp:
		return mPointWarp.get();
	case DX11::PointMirror:
		return mPointMirror.get();
	case DX11::PointClamp:
		return mPointClamp.get();
	case DX11::PointBorder:
		return mPointBorder.get();
	case DX11::SampTotal:
	default:
		g_SysLog->Log(_ERROR, "Error SamplerType %d", static_cast<int>(type));
		return nullptr;
	}
}


void DX11::SamplerTool::SetSampler(UINT pStartSlot, SamplerType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "SamplerTool is uninitialized");
		return;
	}
#endif
	ID3D11SamplerState *l_Sampler = Get(type);
	mDevContext->PSSetSamplers(pStartSlot, 1, &l_Sampler);
}

void DX11::SamplerTool::SetSampler(UINT pStartSlot, sptrSampler pSampler)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "SamplerTool is uninitialized");
		return;
	}
#endif
	ID3D11SamplerState *l_Sampler = pSampler.get();
	mDevContext->PSSetSamplers(pStartSlot, 1, &l_Sampler);
}

DX11::sptrSampler DX11::SamplerTool::CreateSampler(std::string pName, D3D11_SAMPLER_DESC pDesc)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "SamplerTool is uninitialized");
		return nullptr;
	}
#endif

	HRESULT hr = S_OK;
	ID3D11SamplerState* l_SamplerState = nullptr;
	auto CreateSamplerLambda = [&](std::string name) ->bool
	{
		l_SamplerState = nullptr;
		hr = mDevice->CreateSamplerState(&pDesc, &l_SamplerState);
		if (FAILED(hr))
		{
			std::string str = "CreateSamplerState " + name + " is failed.";
			g_SysLog->Log(_ERROR, str.c_str());
			return false;
		}
		return true;
	};

	if(!CreateSamplerLambda(pName)) return nullptr;
	return SmartPointer::CreateShared(l_SamplerState);
}