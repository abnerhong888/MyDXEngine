#include "Engine.h"
#include "Common.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr))
	{
		MessageBoxW(NULL, L"Failed to call CoInitialize.", L"Error", MB_ICONERROR);
		return -1;
	}

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
	Engine engine;
	if (engine.Initialize(hInstance, D_WINDOW_NAME, D_WINDOW_CLASS_NAME, D_WINDOW_WIDTH, D_WINDOW_HEIGHT))
	{
		while (engine.ProcessMessages())
		{
			engine.Update();
			engine.RenderFrame();
			Sleep(1);
		}
	}

	engine.Release();
	CoUninitialize();
	return 0;
}
