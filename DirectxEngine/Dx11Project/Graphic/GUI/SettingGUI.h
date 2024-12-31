#ifndef __SETTINGHUI_H__
#define __SETTINGHUI_H__

#include "..\GraphicCommon.h"
#include "..\Font\MyFont.h"
#include "MYGUI.h"

namespace DX11
{
	class SettingGUI
	{
	public:
		SettingGUI();
		static SettingGUI &GetIns();
		bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext, sptrDXWinData pWinData, int pDisplayTexW, int pDisplayTexH);
		void Render(double pFPS, sptrRTVData pRTVData);
		void Render(double pFPS, RTVType pRTVType);
		void Update();
		void ParseMouseKeyboard(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool GetIsResolutionChanged();
		bool GetIsSettingMode()						{ return mIsSettingMode; }
		~SettingGUI();
	protected:

	private:
		bool isInitialized;
		sptrDevice mDevice;
		sptrDevContext mDevContext;
		sptrDXWinData mWinData;
		
		sptrRTVData mRTV;
		MYGUI mGUI;
		
		MT::int4 mViewport;

		bool mIsSettingMode = false;
		bool mIsResolutionChanged = false;
	};
}


#endif

