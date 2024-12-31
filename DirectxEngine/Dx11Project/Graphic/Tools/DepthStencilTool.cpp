#include "DepthStencilTool.h"

bool DX11::DepthStencilTool::isInitialized = false;;
DX11::sptrDevice DX11::DepthStencilTool::mDevice;
DX11::sptrDevContext DX11::DepthStencilTool::mDevContext;

DX11::sptrDSData DX11::DepthStencilTool::mDefault;


bool DX11::DepthStencilTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext, int pWidth, int pHeight)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	mDevice = pDevice;
	isInitialized = true;

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC pDepthBuffDesc;
	ZeroMemory(&pDepthBuffDesc, sizeof(D3D11_TEXTURE2D_DESC));

	pDepthBuffDesc.Width = pWidth;
	pDepthBuffDesc.Height = pHeight;
	pDepthBuffDesc.MipLevels = 1;
	pDepthBuffDesc.ArraySize = 1;
	pDepthBuffDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	pDepthBuffDesc.SampleDesc.Count = 1;
	pDepthBuffDesc.SampleDesc.Quality = 0;
	pDepthBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	pDepthBuffDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDepthBuffDesc.CPUAccessFlags = 0;
	pDepthBuffDesc.MiscFlags = 0;

	//////////////////////////////////////////////////////////////////////////

	//Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	
	mDefault = CreateDepthStencilState("mDefault", pDepthBuffDesc, depthstencildesc);
	if (mDefault == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	return true;
}
ID3D11DepthStencilView *DX11::DepthStencilTool::Get(DSViewType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DepthStencilTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::DefaultDSView:
		return mDefault->GetDSiew();
	default:
		g_SysLog->Log(_ERROR, "Error DSViewType %d", static_cast<int>(type));
		return nullptr;
	}
	
}

ID3D11DepthStencilState *DX11::DepthStencilTool::Get(DSStateType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DepthStencilTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::DefaultDSState:
		return mDefault->GetDSState();
	default:
		g_SysLog->Log(_ERROR, "Error DSStateType %d", static_cast<int>(type));
		return nullptr;
	}

}

void DX11::DepthStencilTool::SetDepthStecilState(DSStateType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DepthStencilTool is uninitialized");
		return;
	}
#endif
	ID3D11DepthStencilState *l_State = Get(type);
	mDevContext->OMSetDepthStencilState(l_State, 0);
}

DX11::sptrDSData DX11::DepthStencilTool::CreateDepthStencilState(
	std::string pName, 
	D3D11_TEXTURE2D_DESC pDepthBuffDesc,
	D3D11_DEPTH_STENCIL_DESC pDepthstencildesc
	)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DepthStencilTool is uninitialized");
		return nullptr;
	}
#endif
	HRESULT hr = S_OK;
	ID3D11Texture2D *l_DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView *l_DepthStencilView = nullptr;
	ID3D11DepthStencilState * l_depthStencilState = nullptr;

	//Create the Depth/Stencil View
	hr = mDevice->CreateTexture2D(&pDepthBuffDesc, NULL, &l_DepthStencilBuffer);
	if (FAILED(hr))
	{
		std::string str = pName + " DepthStencil CreateTexture2D is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return nullptr;
	}

	hr = mDevice->CreateDepthStencilView(l_DepthStencilBuffer, NULL, &l_DepthStencilView);
	if (FAILED(hr))
	{
		std::string str = pName + " CreateDepthStencilView is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return nullptr;
	}

	hr = mDevice->CreateDepthStencilState(&pDepthstencildesc, &l_depthStencilState);
	if (FAILED(hr))
	{
		std::string str = pName + " CreateDepthStencilState is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return nullptr;
	}
	DSData *l_Data = new DSData(l_DepthStencilView, l_DepthStencilBuffer, l_depthStencilState);

	return SmartPointer::CreateShared(l_Data);
}

DX11::sptrDSData DX11::DepthStencilTool::CreateDepthStencilState(std::string pName, int pWidth, int pHeight)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DepthStencilTool is uninitialized");
		return nullptr;
	}
#endif

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC l_DepthBuffDesc;
	ZeroMemory(&l_DepthBuffDesc, sizeof(D3D11_TEXTURE2D_DESC));

	l_DepthBuffDesc.Width = pWidth;
	l_DepthBuffDesc.Height = pHeight;
	l_DepthBuffDesc.MipLevels = 1;
	l_DepthBuffDesc.ArraySize = 1;
	l_DepthBuffDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	l_DepthBuffDesc.SampleDesc.Count = 1;
	l_DepthBuffDesc.SampleDesc.Quality = 0;
	l_DepthBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	l_DepthBuffDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	l_DepthBuffDesc.CPUAccessFlags = 0;
	l_DepthBuffDesc.MiscFlags = 0;

	//////////////////////////////////////////////////////////////////////////

	//Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC l_Depthstencildesc;
	ZeroMemory(&l_Depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	l_Depthstencildesc.DepthEnable = true;
	l_Depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	l_Depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	HRESULT hr = S_OK;
	ID3D11Texture2D *l_DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView *l_DepthStencilView = nullptr;
	ID3D11DepthStencilState * l_depthStencilState = nullptr;

	//Create the Depth/Stencil View
	hr = mDevice->CreateTexture2D(&l_DepthBuffDesc, NULL, &l_DepthStencilBuffer);
	if (FAILED(hr))
	{
		std::string str = pName + " DepthStencil CreateTexture2D is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return nullptr;
	}

	hr = mDevice->CreateDepthStencilView(l_DepthStencilBuffer, NULL, &l_DepthStencilView);
	if (FAILED(hr))
	{
		std::string str = pName + " CreateDepthStencilView is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return nullptr;
	}

	hr = mDevice->CreateDepthStencilState(&l_Depthstencildesc, &l_depthStencilState);
	if (FAILED(hr))
	{
		std::string str = pName + " CreateDepthStencilState is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return nullptr;
	}
	DSData *l_Data = new DSData(l_DepthStencilView, l_DepthStencilBuffer, l_depthStencilState);

	return SmartPointer::CreateShared(l_Data);
}
//////////////////////////////////////////////////////////////////////////
DX11::DSData::DSData(
	ID3D11DepthStencilView		*pDSView,
	ID3D11Texture2D				*pDSBuffer,
	ID3D11DepthStencilState		*pDSState
)
{
	this->mDepthStencilView = pDSView;
	this->mDepthStencilBuffer = pDSBuffer;
	this->mDepthStencilState = pDSState;
}

ID3D11DepthStencilView		*DX11::DSData::GetDSiew()const
{
	return mDepthStencilView;
}

ID3D11Texture2D				*DX11::DSData::GetDSBuffer()const
{
	return mDepthStencilBuffer;
}

ID3D11DepthStencilState		*DX11::DSData::GetDSState()const
{
	return mDepthStencilState;
}

void DX11::DSData::Release()
{
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mDepthStencilBuffer);
	SAFE_RELEASE(mDepthStencilState);
}