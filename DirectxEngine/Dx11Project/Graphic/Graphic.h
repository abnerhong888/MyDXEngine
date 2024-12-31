#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

// DirectX 11
#include "GraphicTools.h"

namespace DX11
{

class Graphics
{
public:
	bool Initialize(std::vector<WindowInfo> pWinInfos);

	//- DirectX 11 initialize Procedure 
	bool InitializeDXDeviceMainWindow(bool isGPU, std::vector<WindowInfo> pWinInfos); 
	bool InitializeDX11Tools(sptrDevice pDevice, sptrDevContext pDevContext, int pDisplayTexW, int pDisplayTexH);

	void Render(double pFPS);
	void Release();
	void Update();
	void ParseMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, void *userdata);
	static void ParseMsgStaticEntry(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, void *userdata);

	std::vector<sptrAdapter> *mAdapters;
	sptrDevice Device;
	sptrDevContext DevContext;
	int mDisplayTexW = 1920;
	int mDisplayTexH = 1080;
	
protected:
	//- Font
	bool InitializeDXFont();
	//- STL
	bool InitializeDXSTL();
	//- SRV
	bool InitializeImgSRV();
	//- GUI
	bool InitializeGUI();
private:
	std::vector<WindowInfo> mWinInfos;
	
	//Shader Resource Views
	sptrTexSRV mGirlSRV;
	//Font
	MyFont mFont;
	// GUI
	MYGUI mGUI;
	//STL
	MySTL mTeaPotSTL;
};




}; // namespace DX11
#endif // __GRAPHIC_H__