#ifndef __GRAPHICEXAMPLE_H__
#define __GRAPHICEXAMPLE_H__

#include "GraphicTools.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"DXGI.lib")

/************************************************************************/
/* Graphic Tool Example                                                 */
/************************************************************************/

// if you want log something please declare log in global and create shared
// std::shared_ptr<ErrorLogger> g_SysLog;
// g_SysLog = SmartPointer::CreateShared(new ErrorLogger("sysLog"));

namespace DX11
{
	class GraphicExample
	{
	public:
		/*
		- this is sample that it create DirectX device, device context, render target window
		*/
		static bool InitDXDeviceMainWindow(bool isGPU, std::vector<WindowInfo> pWinInfos)
		{
			mDisplayTexW = 1920;
			mDisplayTexH = 1080;
			mWindowInfos = pWinInfos;


			// Adapter
			if (!DXAdapterTool::initialize()) return false;

			mAdapters = &DXAdapterTool::GetAdapters();

			IDXGIAdapter *l_Adapter = isGPU ? DXAdapterTool::getGPUAdapter() : DXAdapterTool::getCPUAdapter();

			// Device
			if (!DXDeviceTool::initialize(l_Adapter)) return false;
			mDevice = DXDeviceTool::GetDevice();
			mDevContext = DXDeviceTool::GetDeviceContext();

			//Render Target Window
			//MainWindow
			if (!DXWIndowTool::Initialize(mDevice, mDevContext)) return false;
			if (!DXWIndowTool::CreateDXWindow(MainWindow, pWinInfos[MainWindow], l_Adapter, WinFormat_8_Bit, 60, false, true)) return false;
			//Window2
			///DXWIndowTool::CreateDXWindow(Window2, pWinInfos[Window2], l_Adapter, WinFormat_8_Bit, 60, false, true);
			//Window3
			///DXWIndowTool::CreateDXWindow(Window3, pWinInfos[Window3], l_Adapter, WinFormat_8_Bit, 60, false, true);

			
			return true;
		}

		/*
		- Initialize all tools, tools already have created some DirectX method that you can use
		*/
		static bool InitDX11Tools(sptrDevice pDevice, sptrDevContext pDevContext, int pDisplayTexW, int pDisplayTexH)
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

		static bool InitTestFontAndRV()
		{
			// Font object example
			if (!mFont.Initialize(L".\\font\\Arial27.font", mDevice, mDevContext)) return false;

			// create image shader resource view
			mPicutreSRV = TextureTool::CreateSRVFromFile_2D(L".\\girl.jpg");
			if (mPicutreSRV == nullptr) { ErrorLogger::MsgBoxLog("\nImage initialize is Failed !\nPlease check your img folder."); }
			
			return true;
		}

		static bool InitializeGUI()
		{
			if (!SettingGUI::GetIns().Initialize(mDevice, mDevContext, DXWIndowTool::GetSptr(MainWindow), mDisplayTexW, mDisplayTexH))
				return false;
		}

		static void RenderTest()
		{
			RenderTool::SetRenderTargetView(OutView);
			RenderTool::SetVertexDataType(TriangleList);
			RenderTool::SetViewPort(0, 0, mDisplayTexW, mDisplayTexH);
			RenderTool::SetSampler(0, LinearWarp);
			RenderTool::SetShaderRV(0, mPicutreSRV->SRV);
			RenderTool::SetShader(Tex2D);
			RenderTool::SetMeshDraw(PlaneMesh, DrawIndices);

			RenderTool::SetRenderTargetView(OutView, false);
			RenderTool::SetViewPort(0, 0, mDisplayTexW, mDisplayTexH);
			mFont.DrawString(100, 100, 50, ColorType::Red, L"Hello World !");
			mFont.DrawString(100, 200, 50, ColorType::Green, L"Hello World !" );
			mFont.DrawString(100, 300, 50, ColorType::Blue, L"Hello World !");

			// Setting Render
			SettingGUI::GetIns().Render(0, OutView);

			RenderTool::SetRenderTargetWindow(MainWindow);
			RenderTool::SetShaderRV(0, RTVTool::Get(OutView)->GetSRV());
			RenderTool::SetVertexDataType(TriangleList);
			RenderTool::SetViewPort(DXWIndowTool::Get(MainWindow)->GetWinViewPort());
			RenderTool::SetSampler(0, LinearWarp);
			RenderTool::SetRasterizer(Solid_None);
			RenderTool::SetShader(Tex2D);
			RenderTool::SetMeshDraw(PlaneMesh, DrawIndices);

			RenderTool::Flush(MainWindow);
		}

		static void Update()
		{
			SettingGUI::GetIns().Update();

			if (SettingGUI::GetIns().GetIsResolutionChanged())
			{
				/*float l_RTWW = (float)DXWIndowTool::Get(MainWindow)->GetWindowInfo().size.w;
				float l_RTWH = (float)DXWIndowTool::Get(MainWindow)->GetWindowInfo().size.h;
				mGUI.SetRTWSize(MT::float2(l_RTWW, l_RTWH));*/
			}
		}
		static void ParseMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, void *userdata)
		{
			SettingGUI::GetIns().ParseMouseKeyboard(hWnd, message, wParam, lParam);

			if (!SettingGUI::GetIns().GetIsSettingMode())
			{
				GraphicExample *l_gfx = reinterpret_cast<GraphicExample*> (userdata);
				DXWIndowTool::ParseFullScreenMsg(hWnd, message, wParam, lParam);
			}
		}
		static void ParseMsgStaticEntry(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, void *userdata)
		{
			return (reinterpret_cast<DX11::GraphicExample *>(userdata))->ParseMsg(hWnd, message, wParam, lParam, userdata);
		}

		static std::vector<WindowInfo> mWindowInfos;
		static std::vector<DX11::sptrAdapter> *mAdapters;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;
		static int mDisplayTexW;
		static int mDisplayTexH;
		static sptrTexSRV mPicutreSRV;
		static MyFont mFont;
	protected:
	private:

	};
}



#endif