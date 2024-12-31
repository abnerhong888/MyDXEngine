#include "Graphic.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"DXGI.lib")

//#if !defined(_LIB)
#if defined(_DEBUG) || defined(DEBUG)
#pragma comment(lib, "DirectXTKd.lib")
#elif defined(NDEBUG) || defined(Release)
#pragma comment(lib, "DirectXTK.lib")
#endif
//#endif

void DX11::Graphics::Release()
{

#if (defined(_DEBUG) || defined(DEBUG)) && false
	/*
	-- please don't worry about this, because all object is created by smart pointer	--
	-- Device is release first, ant then release "other instance object",				--
	-- like SamplerTool object, so it will warning first after released Device object,	--
	-- and release "other instance object", pretty normal.								--
	*/

	// show live device object status
	ID3D11Debug *debugDev = nullptr;

	Device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));
	HRESULT hr =  debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

	debugDev->Release();
	debugDev = nullptr;
#endif
}

bool DX11::Graphics::Initialize(std::vector<WindowInfo> pWinInfos)
{
	if (!InitializeDXDeviceMainWindow(true, pWinInfos)) { return false; }
	if (!InitializeDX11Tools(Device, DevContext, mDisplayTexW, mDisplayTexH)) { return false; }
	if (!InitializeDXFont()) { return false; }
	if (!InitializeDXSTL()) { return false; }

	if (!InitializeImgSRV())
	{
		ErrorLogger::MsgBoxLog("\nImage initialize is Failed !\nPlease check your img folder.");
	}

	if (!InitializeGUI()) { return false; }
	return true;
}

bool DX11::Graphics::InitializeDXDeviceMainWindow(bool isGPU, std::vector<WindowInfo> pWinInfos)
{
	mWinInfos = pWinInfos;

	// Adapter
	if (!DXAdapterTool::initialize()) return false;
	mAdapters = DXAdapterTool::GetAdaptersPtr();
	IDXGIAdapter *l_Adapter = isGPU ? DXAdapterTool::getGPUAdapter() : DXAdapterTool::getCPUAdapter();
	if (l_Adapter == nullptr && isGPU)
	{
		l_Adapter = DXAdapterTool::getCPUAdapter();
		g_SysLog->Log(_WARNING, "Gpu is not available, using Cpu display !");
	}
	// Device
	if (!DXDeviceTool::initialize(l_Adapter)) return false;
	Device = DXDeviceTool::GetDevice();
	DevContext = DXDeviceTool::GetDeviceContext();

	//MainWindow
	if (!DXWIndowTool::Initialize(Device, DevContext)) return false;
	if (!DXWIndowTool::CreateDXWindow(MainWindow, mWinInfos[MainWindow], l_Adapter, WinFormat_8_Bit, 60, false, true)) return false;
	//Window2
	///DXWIndowTool::CreateDXWindow(Window2, mWinInfos[Window2], l_Adapter, WinFormat_8_Bit, 60, false, true);
	//Window3
	///DXWIndowTool::CreateDXWindow(Window3, mWinInfos[Window3], l_Adapter, WinFormat_8_Bit, 60, false, true);

	return true;
}

bool DX11::Graphics::InitializeDX11Tools(sptrDevice pDevice, sptrDevContext pDevContext, int pDisplayTexW, int pDisplayTexH)
{
	//Tools
	if (!TextureTool::Initialize(pDevice, pDevContext)) return false;
	if (!BufferTool::Initialize(pDevice, pDevContext)) return false;
	if (!SamplerTool::Initialize(pDevice, pDevContext)) return false;
	if (!BlendTool::Initialize(pDevice, pDevContext)) return false;
	if (!RasterizerTool::Initialize(pDevice, pDevContext)) return false;
	if (!ShaderTool::Initialize(pDevice, pDevContext)) return false;
	if (!MeshTool::Initialize(pDevice, pDevContext)) return false;
	if (!ConstantBufTool::Initialize(pDevice, pDevContext)) return false;
	if (!DepthStencilTool::Initialize(pDevice, pDevContext, pDisplayTexW, pDisplayTexH)) return false;
	if (!RTVTool::Initialize(pDevice, pDevContext, pDisplayTexW, pDisplayTexH)) return false;
	if (!RenderTool::Initialize(pDevice, pDevContext)) return false;

	return true;
}

bool DX11::Graphics::InitializeDXFont()
{
	if (!mFont.Initialize(D_FONT_FILE, Device, DevContext)) return false;

	return true;
}

bool DX11::Graphics::InitializeDXSTL()
{
	if (!mTeaPotSTL.Initialize(L".\\STL\\TeaPot.stl", Device, DevContext)) return false;
	mTeaPotSTL.InitialCamera(mDisplayTexW, mDisplayTexH);
	return true;
}

bool DX11::Graphics::InitializeImgSRV()
{
	bool isSuccess = true;
	auto l_CreateSRV = [&](sptrTexSRV *pSRV, std::wstring pFilename) ->bool
	{
		*pSRV = TextureTool::CreateSRVFromFile_2D(pFilename);
		if (!*pSRV)
			return false;
		return true;
	};
	//Create SRV Here !

	isSuccess &= l_CreateSRV(&this->mGirlSRV, L"img\\girl.jpg");
	
	return isSuccess;
}

bool DX11::Graphics::InitializeGUI()
{
	if (!SettingGUI::GetIns().Initialize(Device, DevContext, DXWIndowTool::GetSptr(MainWindow), mDisplayTexW, mDisplayTexH))
		return false;


	DXWinData *l_windata = DXWIndowTool::Get(MainWindow);
	MT::int4 l_VP(0, 0, mDisplayTexW, mDisplayTexH);
	if (!mGUI.Initialize("mGUI", Device, DevContext, l_VP, l_windata->GetWindowInfo().size)) return false;

	mGUI.AddBtn("Fullscreen", MT::float4(500.f, 500.f, 200.f, 50.f), L"(F)ullscreen", 'F');
	mGUI.AddBtn("Btn2", MT::float4(500, 600, 200, 50), L"(T)est", 'T', false, true, mGirlSRV);

	

	std::vector<std::pair<int, std::wstring>> l_Items;

	for (int i = 0; i < 30; i++)
	{
		l_Items.emplace_back(std::pair<int, std::wstring>(i, std::to_wstring(i)));

	}
	mGUI.AddListBox("ListBox", MT::float4(200.f, 50.f, 600.f, 200.f), l_Items);

	mGUI.AddComBox("ComBox", MT::float4(900.f, 50.f, 600.f, 50.f), 200.f, l_Items);

	mGUI.AddScrollBar("ScrollBarH", MT::float4(100.f, 800.f, 1500.f, 50.f), _Hor, UIRng(500.f, 1.f, 10.f, 0.f, 2000.f));
	mGUI.AddScrollBar("ScrollBarV", MT::float4(1500.f, 300.f, 50.f, 500.f), _Ver, UIRng(0.f, 1.f, 2.f, 0.f, 1300.f));

	mGUI.AddCheckBox("CheckBox", MT::float4(1300.f, 300.f, 200.f, 30.f), L"Test123", White, true);

	std::vector<std::tuple<int, std::wstring, MT::float4>> l_Ratios;

	l_Ratios.emplace_back(std::tuple<int, std::wstring, MT::float4>(0, L"00000", MT::float4(1300.f, 100.f, 200.f, 30.f)));
	l_Ratios.emplace_back(std::tuple<int, std::wstring, MT::float4>(1, L"11111", MT::float4(1300.f, 150.f, 200.f, 30.f)));
	l_Ratios.emplace_back(std::tuple<int, std::wstring, MT::float4>(2, L"22222", MT::float4(1300.f, 200.f, 200.f, 30.f)));
	mGUI.AddRadios("Radios", l_Ratios, 1, White);
	return true;
}

void DX11::Graphics::Update()
{
	SettingGUI::GetIns().Update();

	if (SettingGUI::GetIns().GetIsResolutionChanged())
	{
		float l_RTWW = (float)DXWIndowTool::Get(MainWindow)->GetWindowInfo().size.w;
		float l_RTWH = (float)DXWIndowTool::Get(MainWindow)->GetWindowInfo().size.h;
		mGUI.SetRTWSize(MT::float2(l_RTWW, l_RTWH));
	}
}

void DX11::Graphics::ParseMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, void *userdata)
{
	SettingGUI::GetIns().ParseMouseKeyboard(hWnd, message, wParam, lParam);

	if (!SettingGUI::GetIns().GetIsSettingMode())
	{
		Graphics *l_gfx = reinterpret_cast<Graphics*> (userdata);
		l_gfx->mTeaPotSTL.ParseMouseKeyboard(hWnd, message, wParam, lParam);

		l_gfx->mGUI.ParseMouseKeyboard(hWnd, message, wParam, lParam);

		DXWIndowTool::ParseFullScreenMsg(hWnd, message, wParam, lParam);
	}
	

}

void DX11::Graphics::ParseMsgStaticEntry(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, void *userdata)
{
	return (reinterpret_cast<DX11::Graphics *>(userdata))->ParseMsg(hWnd, message, wParam, lParam, userdata);
}

void DX11::Graphics::Render(double pFPS)
{
	RenderTool::SetRenderTargetView(OutView);
	RenderTool::SetViewPort(500, 0, mDisplayTexW / 5, mDisplayTexH / 5);
	RenderTool::Plane(LinearWarp, mGirlSRV->SRV);

	//--STL Render

	RenderTool::SetRenderTargetViewDepth(OutView, DefaultDSView, false);
	RenderTool::SetViewPort(0, 0, mDisplayTexW, mDisplayTexH);
	mTeaPotSTL.RenderSTL();

	RenderTool::SetRenderTargetView(OutView, false);
	RenderTool::SetViewPort(0, 0, mDisplayTexW, mDisplayTexH);
	
	mFont.DrawString(50, 100, 50, ColorType::Red, L"\"ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 WA");
	mFont.DrawString(50, 200, 50, ColorType::Green, L"abcdefghijklmnopqrstuvwxyz 1234567890 lai Wa");
	mFont.DrawString(50, 300, 50, ColorType::Blue, L"Abner 1234567890");
	mFont.DrawString(50, 400, 50, ColorType::White, L"\"!`?'.,;:()[]{}<>|/@\\^$-%+=#_&~* 松輝很帥{你好}}好嗎唷@");
	mFont.DrawString(50, 500, 50, ColorType::Purple, L"\"松\"輝很帥你 好-嗎嗎 @ {A} {a} 123-456 Hello");
	mFont.DrawString(50, 600, 50, ColorType::Purple, L"[123-456} [Hello_Aa\\]");
	mFont.DrawString(50, 700, 50, ColorType::Purple, L"asd3817401@gmail.com");

	//--GUI
	mGUI.Render();


	float value = mGUI.GetOBJ<GUIScrollBar>("ScrollBarH")->GetCurrentVal();
	RenderTool::SetRenderTargetView(OutView, false);
	RenderTool::SetViewPort(0, 0, mDisplayTexW, mDisplayTexH);
	mFont.DrawString(650, 900, 30, ColorType::White, L"val1 = %.1f", value);
	
	float value2 = mGUI.GetOBJ<GUIScrollBar>("ScrollBarV")->GetCurrentVal();
	RenderTool::SetRenderTargetView(OutView, false);
	RenderTool::SetViewPort(0, 0, mDisplayTexW, mDisplayTexH);
	mFont.DrawString(1600, 400, 30, ColorType::White, L"val2 = %.1f", value2);



	RenderTool::SetRenderTargetView(OutView, false);
	RenderTool::SetViewPort(0, 0, mDisplayTexW, mDisplayTexH);
	RenderTool::SetBlend(AlphaBlend);
	RenderTool::Plane(LinearWarp, mGUI.GetSRV());
	RenderTool::SetBlend(NullState);

	// Setting Render
	SettingGUI::GetIns().Render(pFPS, OutView);
	
	// Main Window Output
	RenderTool::SetRenderTargetWindow(MainWindow);
	RenderTool::SetViewPort(DXWIndowTool::Get(MainWindow)->GetWinViewPort());
	RenderTool::Plane(LinearWarp, RTVTool::Get(OutView)->GetSRV());

	

	RenderTool::Flush(MainWindow);
}



