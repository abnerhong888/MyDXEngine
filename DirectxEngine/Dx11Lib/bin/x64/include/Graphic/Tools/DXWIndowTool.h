#ifndef __DXWINDOWTOOL_H__
#define __DXWINDOWTOOL_H__

#include "..\GraphicCommon.h"
#include "AdapterTool.h"
namespace DX11
{
	class DXWinData;
	using sptrDXWinData = std::shared_ptr<DXWinData>;

	enum WindowType
	{
		MainWindow,
		Window2,
		Window3,
		WindowTotal
	};

	enum WindowFormat
	{
		WinFormat_8_Bit = DXGI_FORMAT_R8G8B8A8_UNORM,
		WinFormat_10_Bit = DXGI_FORMAT_R10G10B10A2_UNORM,
	};
	class DXWIndowTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		static bool CreateDXWindow(
			WindowType pWindowType, WindowInfo pWindowInfo, 
			IDXGIAdapter *pAdapter, WindowFormat pWinFormat,
			int pFreq, bool pVSync, bool isWindowed);

		static sptrDXWinData CreateDXWindow(
			DXGI_SWAP_CHAIN_DESC pDesc, WindowInfo pWindowInfo,
			IDXGIAdapter *pAdapter, bool pVSync);

		static ID3D11DeviceContext *CreateDefferedDeviceContext();
		static IDXGISwapChain *CreateSwpaChain(IDXGIAdapter *pAdapter, DXGI_SWAP_CHAIN_DESC pDesc);
		static ID3D11RenderTargetView *CreateRenderTargetWindow(IDXGISwapChain *pSwapChain);
		static DXWinData *Get(WindowType type);
		static sptrDXWinData GetSptr(WindowType type);
		static void SetRenderTargetWindow(WindowType pWindowType, bool pClean = true);
		static void SetRenderTargetWindow(sptrDXWinData pDXWinData, bool pClean = true);
		static void SetFlush(WindowType pWindowType);
		static void SetFlush(sptrDXWinData pDXWinData);
		static void SetFullScreen(WindowType pWindowType, bool pEnable);
		static void SetFullScreen(sptrDXWinData pDXWinData, bool pEnable);
		static void ParseFullScreenMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static void ParseFullScreenMsg(sptrDXWinData pDXWinData, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	public:
		static void SetResolution(WindowType pWindowType, DXGI_MODE_DESC *pDisplayModes, int pIndex);
		static void SetResolution(sptrDXWinData pDXWinData, DXGI_MODE_DESC *pDisplayModes, int pIndex);
	protected:
	private:
		static bool isInitialized;

		static sptrDevice mDevice;
		static sptrDevContext mDevContext;

		static std::unordered_map<WindowType, sptrDXWinData> mWindowsMap;
	};

	class DXWinData
	{
	public:
		DXWinData(
			IDXGISwapChain *pSwapChain,
			ID3D11RenderTargetView *pRenderTargetWindow,
			ID3D11DeviceContext *pDferredDevContext);

		IDXGISwapChain				*GetSwapChain()const;
		ID3D11RenderTargetView		*GetRTWindow()const;
		ID3D11DeviceContext			*GetDeferredDevContext()const;

		void						ResizeSwapChainBuffer();


		void						SetWindowInfo(WindowInfo pWindowInfo);
		WindowInfo					GetWindowInfo()const;

		void						SetWinViewPort(int x, int y, int w, int h);
		D3D11_VIEWPORT				GetWinViewPort()const;

		void						SetFreq(const int pFreq);
		int							GetFreq()const;

		void						SetvSync(const bool pVSync);
		int							GetvSync()const;

		void						SetWindowed(const bool pIsWindowed);
		bool						GetisWindowed()const;

		void						SetWindoweFormat(const WindowFormat pFormatType);
		WindowFormat				GetWindoweFormat()const;

		void						SetAdapter(IDXGIAdapter *pAdapter);
		IDXGIAdapter				*GetAdapter();

		void						SetAdapterOutputData(IDXGIAdapter *pAdapter);
		std::vector<AdapterOutputData> *GetAdapterOutputData();

		bool						SetDisplayModeInfo();
		UINT						GetSupportDisplayModeCount();
		DXGI_MODE_DESC				*GetSupportedDisplayModes();
		void						SetCurrentDisplayMode(DXGI_MODE_DESC pDisplayMode);
		DXGI_MODE_DESC				GetCurrentDisplayMode();
		void 						SetCurrentDisplayModeIdx(int pIndex);
		int							GetCurrentDisplayModeIdx();
		void Release();
	protected:
	private:
		int mDisplayFrequency;
		int mVSync;
		bool misWindowed;
		WindowInfo	mWinInfo;
		D3D11_VIEWPORT mWindowViewPort;

		IDXGISwapChain			*mSwapChain = nullptr;
		ID3D11RenderTargetView	*mRenderTargetWindow = nullptr;
		ID3D11DeviceContext		*mDeferredDevContext = nullptr;
		
		WindowFormat mWindowFormat;
		IDXGIAdapter			*mAdapter = nullptr;
		std::vector<AdapterOutputData> *mAdapterOutputData;
		int mAdapterOutputIdx = 0;

		UINT mSupportedDisplayModesCount;
		DXGI_MODE_DESC* mSupportedDisplayModes = nullptr;
		int mCurrentDisplayModeIdx = 0;
		DXGI_MODE_DESC  mCurrentDisplayMode;
	};
}



#endif
