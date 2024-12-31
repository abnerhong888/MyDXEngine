#include "DXWIndowTool.h"


bool DX11::DXWIndowTool::isInitialized = false;
DX11::sptrDevice DX11::DXWIndowTool::mDevice;
DX11::sptrDevContext DX11::DXWIndowTool::mDevContext;


std::unordered_map<DX11::WindowType, DX11::sptrDXWinData> DX11::DXWIndowTool::mWindowsMap;

bool DX11::DXWIndowTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }
	mDevice = pDevice;
	mDevContext = pDevContext;
	mWindowsMap.clear();
	isInitialized = true;
	return true;
}

bool DX11::DXWIndowTool::CreateDXWindow(
	WindowType pWindowType, WindowInfo pWindowInfo, 
	IDXGIAdapter *pAdapter, WindowFormat pWinFormat,
	int pFreq, bool pVSync, bool isWindowed)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return nullptr;
	}
#endif
	if (pWindowType >= WindowTotal)
	{
		g_SysLog->Log(_ERROR, "Error WindowType %d", static_cast<int>(pWindowType));
		return false;
	}

	// Create swap chain 
	// DirectX 11.0 systems 
	DXGI_SWAP_CHAIN_DESC Desc;
	ZeroMemory(&Desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	Desc.BufferCount = 1;
	Desc.BufferDesc.Width = pWindowInfo.size.w;
	Desc.BufferDesc.Height = pWindowInfo.size.h;
	Desc.BufferDesc.Format = static_cast<DXGI_FORMAT>(pWinFormat);
	Desc.BufferDesc.RefreshRate.Numerator = pFreq;
	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
	Desc.OutputWindow = pWindowInfo.handle;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	Desc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	Desc.Windowed = static_cast<BOOL>(isWindowed);

	IDXGISwapChain *l_SwapChain = CreateSwpaChain(pAdapter, Desc);
	if (l_SwapChain == nullptr) return false;
	ID3D11RenderTargetView *l_RenderTargetWindow = CreateRenderTargetWindow(l_SwapChain);
	if (l_RenderTargetWindow == nullptr) return false;
	ID3D11DeviceContext *l_DeferredDevContext = CreateDefferedDeviceContext();
	if (l_DeferredDevContext == nullptr) return false;

	DXWinData *l_data = new DXWinData(l_SwapChain, l_RenderTargetWindow, l_DeferredDevContext);
	l_data->SetFreq(pFreq);
	l_data->SetvSync(pVSync);
	l_data->SetWindowed(isWindowed);
	l_data->SetWindowInfo(pWindowInfo);
	l_data->SetWinViewPort(0, 0, pWindowInfo.size.w, pWindowInfo.size.h);
	l_data->SetWindoweFormat(pWinFormat);
	l_data->SetAdapter(pAdapter);
	l_data->SetAdapterOutputData(pAdapter);
	bool IsSupportedDisplayMode = l_data->SetDisplayModeInfo();

	sptrDXWinData l_windata = SmartPointer::CreateShared(l_data);

	mWindowsMap[pWindowType] = l_windata;
	
	if (!IsSupportedDisplayMode)
	{
		// if not support display mode, change to lowest mode.
		SetResolution(pWindowType, mWindowsMap[pWindowType]->GetSupportedDisplayModes(), 0);
	}

	return true;
}

DX11::sptrDXWinData DX11::DXWIndowTool::CreateDXWindow(
	DXGI_SWAP_CHAIN_DESC pDesc, WindowInfo pWindowInfo,
	IDXGIAdapter *pAdapter, bool pVSync)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return nullptr;
	}
#endif
	IDXGISwapChain *l_SwapChain = CreateSwpaChain(pAdapter, pDesc);
	if (l_SwapChain == nullptr) return nullptr;
	ID3D11RenderTargetView *l_RenderTargetWindow = CreateRenderTargetWindow(l_SwapChain);
	if (l_RenderTargetWindow == nullptr) return nullptr;
	ID3D11DeviceContext *l_DeferredDevContext = CreateDefferedDeviceContext();
	if (l_DeferredDevContext == nullptr) return nullptr;
	
	DXWinData *l_data = new DXWinData(l_SwapChain, l_RenderTargetWindow, l_DeferredDevContext);
	l_data->SetFreq(pDesc.BufferDesc.RefreshRate.Numerator);
	l_data->SetvSync(pVSync);
	l_data->SetWindowed(pDesc.Windowed > 0 ? true : false);
	l_data->SetWindowInfo(pWindowInfo);
	l_data->SetWinViewPort(0, 0, pWindowInfo.size.w, pWindowInfo.size.h);
	l_data->SetWindoweFormat(static_cast<WindowFormat>(pDesc.BufferDesc.Format));
	l_data->SetAdapter(pAdapter);
	l_data->SetAdapterOutputData(pAdapter);
	bool IsSupportedDisplayMode = l_data->SetDisplayModeInfo();

	sptrDXWinData sptrData = SmartPointer::CreateShared(l_data);
	if (!IsSupportedDisplayMode)
	{
		// if not support display mode, change to lowest mode.
		SetResolution(sptrData, sptrData->GetSupportedDisplayModes(), 0);
	}
	return sptrData;
}

ID3D11DeviceContext *DX11::DXWIndowTool::CreateDefferedDeviceContext()
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return nullptr;
	}
#endif
	HRESULT hr = S_OK;
	ID3D11DeviceContext * l_DeferredDevContext = nullptr;
	hr = mDevice->CreateDeferredContext(0, &(l_DeferredDevContext));

	if (FAILED(hr))
	{
		g_SysLog->Log(_ERROR, "CreateDeferredContext is failed.");
		return nullptr;
	}
	return l_DeferredDevContext;
}

IDXGISwapChain *DX11::DXWIndowTool::CreateSwpaChain(IDXGIAdapter *pAdapter, DXGI_SWAP_CHAIN_DESC pDesc)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return nullptr;
	}
#endif
	HRESULT hr = S_OK;
	sptrIDXGIFactory l_Factory = DX11::DXAdapterTool::GetDXGIFactory(pAdapter);
	
	IDXGISwapChain* l_swapchain = nullptr;
	hr = l_Factory->CreateSwapChain(mDevice.get(), &pDesc, &l_swapchain);

	if (FAILED(hr))
	{
		g_SysLog->Log(_ERROR, "CreateSwapChain is failed.");
		return nullptr;
	}
	return l_swapchain;
}

ID3D11RenderTargetView *DX11::DXWIndowTool::CreateRenderTargetWindow(IDXGISwapChain *pSwapChain)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return nullptr;
	}
#endif

	HRESULT hr = S_OK;

	// Create the back buffer
	ID3D11Texture2D* pBackBuffer = nullptr;
	
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
	{
		g_SysLog->Log(_ERROR, "CreateBackBuffer is failed.");
		return nullptr;
	}

	// get the back buffer desc
	D3D11_TEXTURE2D_DESC backBufferDesc;
	pBackBuffer->GetDesc(&backBufferDesc);

	ID3D11RenderTargetView *l_RenderTargetView = nullptr;
	hr = mDevice->CreateRenderTargetView(pBackBuffer, NULL, &l_RenderTargetView);
	if (FAILED(hr))
	{
		g_SysLog->Log(_ERROR, "CreateRenderTargetView is failed.");
		return false;
	}

	SAFE_RELEASE(pBackBuffer);
	return l_RenderTargetView;
}

DX11::DXWinData *DX11::DXWIndowTool::Get(WindowType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return nullptr;
	}
#endif

	if (type < WindowTotal)
	{
		return mWindowsMap[type].get();
	}
	else
	{
		g_SysLog->Log(_ERROR, "Error WindowType %d", static_cast<int>(type));
		return nullptr;
	}
}

DX11::sptrDXWinData DX11::DXWIndowTool::GetSptr(WindowType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return nullptr;
	}
#endif

	if (type < WindowTotal)
	{
		return mWindowsMap[type];
	}
	else
	{
		g_SysLog->Log(_ERROR, "Error WindowType %d", static_cast<int>(type));
		return nullptr;
	}
}

void DX11::DXWIndowTool::SetRenderTargetWindow(WindowType pWindowType, bool pClean)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return ;
	}
#endif
	ID3D11RenderTargetView *l_targetView = Get(pWindowType)->GetRTWindow();
	mDevContext->OMSetRenderTargets(1, &l_targetView, NULL);
	if (pClean)
	{
		float l_cc[4] = { 0.0, 0.0, 0.0, 0.0 };
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}
}

void DX11::DXWIndowTool::SetRenderTargetWindow(sptrDXWinData pDXWinData, bool pClean)
{
	ID3D11RenderTargetView *l_targetView = pDXWinData->GetRTWindow();
	mDevContext->OMSetRenderTargets(1, &l_targetView, NULL);
	if (pClean)
	{
		float l_cc[4] = { 0.0, 0.0, 0.0, 0.0 };
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}

}

void DX11::DXWIndowTool::SetFlush(WindowType pWindowType)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return;
	}
#endif

	DXWinData *l_data = Get(pWindowType);
	l_data->GetSwapChain()->Present(l_data->GetvSync(), 0);
	mDevContext->ClearState();
}

void DX11::DXWIndowTool::SetFlush(sptrDXWinData pDXWinData)
{
	pDXWinData->GetSwapChain()->Present(pDXWinData->GetvSync(), 0);
	mDevContext->ClearState();
}

void DX11::DXWIndowTool::SetFullScreen(WindowType pWindowType, bool pEnable)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return;
	}
#endif
	DXWinData *l_data = Get(pWindowType);
	if (l_data->GetisWindowed() == pEnable)
	{
		l_data->GetSwapChain()->SetFullscreenState(pEnable, nullptr);
		l_data->SetWindowed(!pEnable);
	}
}

void DX11::DXWIndowTool::SetFullScreen(sptrDXWinData pDXWinData, bool pEnable)
{
	DXWinData *l_data = pDXWinData.get();
	if (l_data->GetisWindowed() == pEnable)
	{
		l_data->GetSwapChain()->SetFullscreenState(pEnable, nullptr);
		l_data->SetWindowed(!pEnable);
	}
}


void DX11::DXWIndowTool::ParseFullScreenMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXWIndowTool is uninitialized");
		return;
	}

#endif
	if (!isInitialized) return;
	if (message == WM_SYSCOMMAND)
	{
		if (SC_KEYMENU == (wParam & 0xFFF0) && (GetKeyState(VK_RETURN) & 0x8000)) // alt - enter
		{
			for (int i = static_cast<int>(WindowType::MainWindow); i < mWindowsMap.size(); i++)
			{
				sptrDXWinData data = mWindowsMap[static_cast<WindowType>(i)];
				if (data->GetWindowInfo().handle == hWnd)
				{
					bool flag = !data->GetisWindowed();
					SetFullScreen(data, !flag);
				}
			}
		}
		else
		{
			DefWindowProc(hWnd, message, wParam, lParam);
		}
	}	
	else if (message == WM_DISPLAYCHANGE)
	{
		for (int i = static_cast<int>(WindowType::MainWindow); i < mWindowsMap.size(); i++)
		{
			sptrDXWinData data = mWindowsMap[static_cast<WindowType>(i)];
			BOOL fullscreen;
			data->GetSwapChain()->GetFullscreenState(&fullscreen, nullptr);
			if (fullscreen == static_cast<int>(data->GetisWindowed()))
			{
				SetFullScreen(data, fullscreen > 0 ? true : false);
			}
		}
	}
}

void DX11::DXWIndowTool::ParseFullScreenMsg(sptrDXWinData pDXWinData, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_SYSCOMMAND)
	{
		if (SC_KEYMENU == (wParam & 0xFFF0) && (GetKeyState(VK_RETURN) & 0x8000)) // alt - enter
		{
			if (hWnd == pDXWinData->GetWindowInfo().handle)
			{
				bool flag = !pDXWinData->GetisWindowed();
				SetFullScreen(pDXWinData, !flag);
			}
		}
		else
		{
			DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	else if (message == WM_DISPLAYCHANGE)
	{
		BOOL fullscreen;
		pDXWinData->GetSwapChain()->GetFullscreenState(&fullscreen, nullptr);
		if (fullscreen == static_cast<int>(pDXWinData->GetisWindowed()))
		{
			SetFullScreen(pDXWinData, fullscreen > 0 ? true : false);
		}
		
	}
}

void DX11::DXWIndowTool::SetResolution(sptrDXWinData pDXWinData, DXGI_MODE_DESC *pDisplayModes, int pIndex)
{
	HRESULT hr = S_OK;
	// Microsoft recommends zeroing out the refresh rate of the description before resizing the targets
	DXGI_MODE_DESC zeroRefreshRate = pDisplayModes[pIndex];
	zeroRefreshRate.RefreshRate.Numerator = 0;
	zeroRefreshRate.RefreshRate.Denominator = 0;

	WindowInfo l_WindowInfo = pDXWinData->GetWindowInfo();
	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - pDisplayModes[pIndex].Width / 2;
	int y = GetSystemMetrics(SM_CYSCREEN) / 2 - pDisplayModes[pIndex].Height / 2;

	int w = pDisplayModes[pIndex].Width;
	int h = pDisplayModes[pIndex].Height;
	l_WindowInfo.size = MT::int2(w, h);
	l_WindowInfo.rect = MT::int4(x, y, w, h);
	pDXWinData->SetWindowInfo(l_WindowInfo);
	pDXWinData->SetWinViewPort(0, 0, w, h);

	bool IsWindowed = pDXWinData->GetisWindowed();
	if (IsWindowed)
	{
		RECT l_rect = { x, y, w, h };
		AdjustWindowRect(&l_rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU/*WS_POPUP*/, FALSE);
		SetWindowPos(pDXWinData->GetWindowInfo().handle, NULL, x, y, w, h, SWP_SHOWWINDOW);
	}

	hr = pDXWinData->GetSwapChain()->ResizeTarget(&zeroRefreshRate);
	if (FAILED(hr))
	{
		g_SysLog->Log(_ERROR, "SetResolution -> ResizeTarget is failed. ");
		return;
	}

	mDevContext->ClearState();
	pDXWinData->ResizeSwapChainBuffer();

	pDXWinData->SetCurrentDisplayModeIdx(pIndex);
	pDXWinData->SetCurrentDisplayMode(pDisplayModes[pIndex]);
}

void DX11::DXWIndowTool::SetResolution(WindowType pWindowType, DXGI_MODE_DESC *pDisplayModes, int pIndex)
{
	SetResolution(mWindowsMap[pWindowType], pDisplayModes, pIndex);
}


//////////////////////////////////////////////////////////////////////////

DX11::DXWinData::DXWinData(
	IDXGISwapChain *pSwapChain,
	ID3D11RenderTargetView *pRenderTargetWindow,
	ID3D11DeviceContext *pDferredDevContext)
{
	this->mSwapChain = pSwapChain;
	this->mRenderTargetWindow = pRenderTargetWindow;
	this->mDeferredDevContext = pDferredDevContext;
}

IDXGISwapChain *DX11::DXWinData::GetSwapChain()const
{
	return mSwapChain;
}

ID3D11RenderTargetView *DX11::DXWinData::GetRTWindow()const
{
	return mRenderTargetWindow;
}

ID3D11DeviceContext	*DX11::DXWinData::GetDeferredDevContext()const
{
	return mDeferredDevContext;
}

void DX11::DXWinData::ResizeSwapChainBuffer()
{
	SAFE_RELEASE(mRenderTargetWindow);

	HRESULT hr = mSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	if (FAILED(hr))
	{
		g_SysLog->Log(_ERROR, "ResizeSwapChainBuffer -> ResizeBuffers is failed. ");
	}
	
	mRenderTargetWindow = DXWIndowTool::CreateRenderTargetWindow(mSwapChain);
	if (mRenderTargetWindow == nullptr)
	{
		g_SysLog->Log(_ERROR, "ResizeSwapChainBuffer -> CreateRenderTargetWindow is failed. ");
	}
}

void DX11::DXWinData::SetWindowInfo(WindowInfo pWindowInfo)
{
	mWinInfo = pWindowInfo;
}

WindowInfo DX11::DXWinData::GetWindowInfo()const
{
	return mWinInfo;
}

void DX11::DXWinData::SetWinViewPort(int x, int y, int w, int h)
{
	mWindowViewPort.TopLeftX = static_cast<float>(x);
	mWindowViewPort.TopLeftY = static_cast<float>(y);
	mWindowViewPort.Width = static_cast<float>(w);
	mWindowViewPort.Height = static_cast<float>(h);
	mWindowViewPort.MinDepth = 0.0f;
	mWindowViewPort.MaxDepth = 1.0f;
}

D3D11_VIEWPORT DX11::DXWinData::GetWinViewPort()const
{
	return mWindowViewPort;
}

void DX11::DXWinData::SetFreq(const int pFreq)
{
	mDisplayFrequency = pFreq;
}

int	DX11::DXWinData::GetFreq()const
{
	return mDisplayFrequency;
}

void DX11::DXWinData::SetvSync(const bool pVSync)
{
	mVSync = static_cast<int>(pVSync);
}

int	DX11::DXWinData::GetvSync()const
{
	return mVSync;
}

void DX11::DXWinData::SetWindowed(const bool pIsWindowed)
{
	misWindowed = pIsWindowed;
}

bool DX11::DXWinData::GetisWindowed()const
{
	return misWindowed;
}

void DX11::DXWinData::SetWindoweFormat(const WindowFormat pFormatType)
{
	mWindowFormat = pFormatType;
}

DX11::WindowFormat DX11::DXWinData::GetWindoweFormat()const
{
	return mWindowFormat;
}

void DX11::DXWinData::SetAdapter(IDXGIAdapter *pAdapter)
{
	mAdapter = pAdapter;
}
IDXGIAdapter *DX11::DXWinData::GetAdapter()
{
	return mAdapter;
}

void DX11::DXWinData::SetAdapterOutputData(IDXGIAdapter *pAdapter)
{
	std::vector<sptrAdapter> *l_Adapters = DXAdapterTool::GetAdaptersPtr();

	for (sptrAdapter adapter : *l_Adapters)
	{
		if (adapter->mAdapter == pAdapter)
		{
			mAdapterOutputData = &adapter->mOutputs;
			break;
		}
	}
}

std::vector<DX11::AdapterOutputData> *DX11::DXWinData::GetAdapterOutputData()
{
	return mAdapterOutputData;
}

bool DX11::DXWinData::SetDisplayModeInfo()
{
	IDXGIOutput *l_Output = nullptr;
	if (FAILED(mSwapChain->GetContainingOutput(&l_Output))) {}
	DXGI_OUTPUT_DESC l_Des = { 0 };
	l_Output->GetDesc(&l_Des);

	bool IsSupportedMode = false;
	for (int i = 0; i < (*mAdapterOutputData).size(); i++)
	{
		std::string str1 = StringConverter::WideToString((*mAdapterOutputData)[i].mDescription.DeviceName);
		std::string str2 = StringConverter::WideToString(l_Des.DeviceName);
		if (str1.compare(str2) == 0)
		{
			mAdapterOutputIdx = i;

			HRESULT hr = l_Output->GetDisplayModeList(static_cast<DXGI_FORMAT>(mWindowFormat), 0, &mSupportedDisplayModesCount, nullptr);
			if (FAILED(hr)) g_SysLog->Log(_ERROR, "SetAdapterOutputData -> GetDisplayModeList count is failed.");
			mSupportedDisplayModes = new DXGI_MODE_DESC[mSupportedDisplayModesCount];
			ZeroMemory(mSupportedDisplayModes, sizeof(DXGI_MODE_DESC) * mSupportedDisplayModesCount);

			hr = l_Output->GetDisplayModeList(static_cast<DXGI_FORMAT>(mWindowFormat), 0,
				&mSupportedDisplayModesCount, mSupportedDisplayModes);
			if (FAILED(hr)) g_SysLog->Log(_ERROR, "SetAdapterOutputData -> GetDisplayModeList is failed.");

			
			for (UINT j = 0; j < mSupportedDisplayModesCount; j++)
			{
				if (mWinInfo.size.w == mSupportedDisplayModes[j].Width &&
					mWinInfo.size.h == mSupportedDisplayModes[j].Height)
				{
					IsSupportedMode = true;
					mCurrentDisplayMode = mSupportedDisplayModes[j];
					mCurrentDisplayModeIdx = j;
					break;
				}
			}

			break;
		}
	}
	l_Output->Release();

	if (!IsSupportedMode)
	{
		g_SysLog->Log(_WARNING, "SetAdapterOutputData -> Current display mode is not supported, change to lowest mode.");
		mCurrentDisplayMode = mSupportedDisplayModes[0];
		mCurrentDisplayModeIdx = 0;
		return false;
	}

	return true;
}

UINT DX11::DXWinData::GetSupportDisplayModeCount()
{
	return mSupportedDisplayModesCount;
}

DXGI_MODE_DESC *DX11::DXWinData::GetSupportedDisplayModes()
{
	return mSupportedDisplayModes;
}

void DX11::DXWinData::SetCurrentDisplayMode(DXGI_MODE_DESC pDisplayMode)
{
	mCurrentDisplayMode = pDisplayMode;
}

DXGI_MODE_DESC DX11::DXWinData::GetCurrentDisplayMode()
{
	return mCurrentDisplayMode;
}

void DX11::DXWinData::SetCurrentDisplayModeIdx(int pIndex)
{
	mCurrentDisplayModeIdx = pIndex;
}

int	DX11::DXWinData::GetCurrentDisplayModeIdx()
{
	return mCurrentDisplayModeIdx;
}

void DX11::DXWinData::Release()
{
	BOOL fullscreen;
	mSwapChain->GetFullscreenState(&fullscreen, nullptr);
	if (fullscreen)
	{
		mSwapChain->SetFullscreenState(false, nullptr);
	}
	SAFE_RELEASE(mSwapChain);
	SAFE_RELEASE(mRenderTargetWindow);
	SAFE_RELEASE(mDeferredDevContext);

	SAFE_DELETE(mSupportedDisplayModes);
}
