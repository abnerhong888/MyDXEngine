#include "SettingGUI.h"

   

DX11::SettingGUI::SettingGUI()
{
}


DX11::SettingGUI::~SettingGUI()
{
}

DX11::SettingGUI &DX11::SettingGUI:: GetIns()
{
	static SettingGUI l_ins;
	return l_ins;
}

bool DX11::SettingGUI::Initialize(sptrDevice pDevice, sptrDevContext pDevContext, sptrDXWinData pWinData, int pDisplayTexW, int pDisplayTexH)
{
	if (isInitialized) return true;

	mDevice = pDevice;
	mDevContext = pDevContext;
	mWinData = pWinData;
	MT::int2 l_RTWSize = mWinData->GetWindowInfo().size;
	
	mViewport = MT::int4 (0, 0, pDisplayTexW, pDisplayTexH);
	mGUI.Initialize("SettingGUI", mDevice, mDevContext, mViewport, l_RTWSize);
	MyFont::GetIns().Initialize(D_FONT_FILE, mDevice, mDevContext);

	mRTV = RTVTool::CreateRTV("mSettingRTV", pDisplayTexW, pDisplayTexH, RENDER_SRV_TARGET, RGBA8_U);
	if (mRTV == nullptr) return false;
	
	mGUI.AddBtn("SettingBtn", MT::float4(pDisplayTexW - 100.f, 0.f, 100.f, 50.f), L"Setting", 0, false, false);
	mGUI.AddBtn("SettingOKBtn", MT::float4(10.f + 300.f, 800.f, 100.f, 50.f), L"OK");
	mGUI.AddBtn("SettingCancelBtn", MT::float4(10.f + 450.f, 800.f, 100.f, 50.f), L"Cancel");
	mGUI.AddBtn("SettingExitBtn", MT::float4(10.f + 300.f, 900.f, 300.f, 50.f), L"Exit Program");

	std::vector<std::pair<int, std::wstring>> ScreenModeItems;
	ScreenModeItems.emplace_back(std::pair<int, std::wstring>(0, L"Windowed"));
	ScreenModeItems.emplace_back(std::pair<int, std::wstring>(1, L"Full Screen"));
	int ScreenModeDefaultIdx = mWinData->GetisWindowed() ? 0 : 1;
	mGUI.AddComBox("SettingScreenMode", MT::float4(10.f + 300.f, 100.f, 500.f, 50.f), 200.f, ScreenModeItems, ScreenModeDefaultIdx);
	
	std::vector<std::pair<int, std::wstring>> ResolutionItems;
	DXGI_MODE_DESC *desc = mWinData->GetSupportedDisplayModes();
	for (UINT i = 0; i < mWinData->GetSupportDisplayModeCount(); i++)
	{
		std::wstring str = std::to_wstring(desc[i].Width) + L" x " + std::to_wstring(desc[i].Height);
		ResolutionItems.emplace_back(std::pair<int, std::wstring>(i, str));
	}
	mGUI.AddComBox("SettingResolution", MT::float4(10.f + 300.f, 160.f, 500.f, 50.f), 200.f, ResolutionItems, mWinData->GetCurrentDisplayModeIdx());
	
	isInitialized = true;
	return true;
}

void DX11::SettingGUI::Render(double pFPS, sptrRTVData pRTVData)
{
	if (!isInitialized) return;
	mGUI.Render();
	RenderTool::SetRenderTargetView(mRTV, true);
	RenderTool::SetViewPort(mViewport);
	RenderTool::SetBlend(AlphaBlend);
	RenderTool::PlaneColor(LinearWarp, CadetBlue, mIsSettingMode? 1.0f : 0.0f);
	RenderTool::Plane(LinearWarp, mGUI.GetSRV());
	RenderTool::SetBlend(NullState);

	RenderTool::SetRenderTargetView(pRTVData, false);
	RenderTool::SetViewPort(mViewport);
	RenderTool::SetBlend(AlphaBlend);
	RenderTool::Plane(LinearWarp, mRTV->GetSRV());
	RenderTool::SetBlend(NullState);

	if(!mIsSettingMode)
		MyFont::GetIns().DrawString(10, 30, 30, ColorType::White, L"FPS : %0.1f", pFPS);
	else
	{
		MyFont::GetIns().DrawString(10, 50, 30, ColorType::White, L"DirectX11 3D Settings");
		MyFont::GetIns().DrawString(10, 140, 30, ColorType::White, L"Screen Mode");
		MyFont::GetIns().DrawString(10, 200, 30, ColorType::White, L"Resolution");
	}
		
}

void DX11::SettingGUI::Render(double pFPS, RTVType pRTVType)
{
	this->Render(pFPS, RTVTool::GetSptr(pRTVType));
}

void DX11::SettingGUI::ParseMouseKeyboard(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!isInitialized) return;
	mGUI.ParseMouseKeyboard(hWnd, message, wParam, lParam);
}

void DX11::SettingGUI::Update()
{
	if (!isInitialized) return;

	if (mGUI.GetOBJ<GUIButton>("SettingBtn")->GetEvented())
	{
		mIsSettingMode = !mIsSettingMode;
	}
	if (mIsSettingMode)
	{
		mGUI.GetOBJ<GUIButton>("SettingBtn")->SetEnable(false);
		mGUI.GetOBJ<GUIComBox>("SettingScreenMode")->SetEnable(true);
		mGUI.GetOBJ<GUIComBox>("SettingResolution")->SetEnable(true);
		mGUI.GetOBJ<GUIButton>("SettingOKBtn")->SetEnable(true);
		mGUI.GetOBJ<GUIButton>("SettingCancelBtn")->SetEnable(true);
		mGUI.GetOBJ<GUIButton>("SettingExitBtn")->SetEnable(true);

		if (mGUI.GetOBJ<GUIButton>("SettingExitBtn")->GetEvented())
		{
			PostMessage(mWinData->GetWindowInfo().handle, WM_CLOSE, 0, 0);
		}
		// Cancel
		if (mGUI.GetOBJ<GUIButton>("SettingCancelBtn")->GetEvented())
		{
			int ScreenModeidx = mWinData->GetisWindowed() ? 0 : 1;
			if (mGUI.GetOBJ<GUIComBox>("SettingScreenMode")->GetSelectedIdx() != ScreenModeidx)
			{
				mGUI.GetOBJ<GUIComBox>("SettingScreenMode")->SetSelectedIdx(ScreenModeidx);
			}

			mGUI.GetOBJ<GUIComBox>("SettingResolution")->SetSelectedIdx(mWinData->GetCurrentDisplayModeIdx());

			mIsSettingMode = false;
		}
		// OK
		if (mGUI.GetOBJ<GUIButton>("SettingOKBtn")->GetEvented())
		{
			if (mGUI.GetOBJ<GUIComBox>("SettingScreenMode")->GetSelectedIdx() == 1 && mWinData->GetisWindowed())
			{
				DXWIndowTool::SetFullScreen(mWinData, true);
			}
			else if (mGUI.GetOBJ<GUIComBox>("SettingScreenMode")->GetSelectedIdx() == 0 && !mWinData->GetisWindowed())
			{
				DXWIndowTool::SetFullScreen(mWinData, false);
			}

			if (mWinData->GetCurrentDisplayModeIdx() != mGUI.GetOBJ<GUIComBox>("SettingResolution")->GetSelectedIdx())
			{
				int ResolutionIdx = mGUI.GetOBJ<GUIComBox>("SettingResolution")->GetSelectedIdx();

				DXWIndowTool::SetResolution(mWinData, mWinData->GetSupportedDisplayModes(), ResolutionIdx);
				float l_RTWW = (float)mWinData->GetWindowInfo().size.w;
				float l_RTWH = (float)mWinData->GetWindowInfo().size.h;
				mGUI.SetRTWSize(MT::float2(l_RTWW, l_RTWH));
				mIsResolutionChanged = true;
			}
			mIsSettingMode = false;
		}

	}
	else
	{
		mGUI.GetOBJ<GUIButton>("SettingBtn")->SetEnable(true);
		mGUI.GetOBJ<GUIComBox>("SettingScreenMode")->SetEnable(false);
		mGUI.GetOBJ<GUIComBox>("SettingResolution")->SetEnable(false);
		mGUI.GetOBJ<GUIButton>("SettingOKBtn")->SetEnable(false);
		mGUI.GetOBJ<GUIButton>("SettingCancelBtn")->SetEnable(false);
		mGUI.GetOBJ<GUIButton>("SettingExitBtn")->SetEnable(false);
	}
}

bool DX11::SettingGUI::GetIsResolutionChanged()
{
	if (!isInitialized) return false;

	if (mIsResolutionChanged)
	{
		mIsResolutionChanged = false;
		return true;
	}
	return false;
}