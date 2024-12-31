
#include "Engine.h"

std::shared_ptr<ErrorLogger> g_SysLog;

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	if (WinApp.CheckProcessExist(StringConverter::StringToWide(window_title)))
	{
		return false;
	}
	
	g_SysLog = SmartPointer::CreateShared(new ErrorLogger("sysLog"));
	g_SysLog->LogFileShouldBeDelete(D_LOGFILE_DELETE_DAYS);

	g_SysLog->Log(_INFO, "Initialize starting\n");

	// Windows Application
	if (!WinApp.Initialize(hInstance, window_title, window_class, width, height))
	{
		g_SysLog->Log(_ERROR, "Windows application initialize failed \n");
		return false;
	}
	g_SysLog->Log(_INFO, "Windows application initialize success \n");

	// DirectX 11 
	g_SysLog->Log(_INFO, "--------DirectX 11 initialize start-------- \n");

	if (!this->gfx.Initialize(WinApp.GetWindowInfos()))
	{
		g_SysLog->Log(_ERROR, "--------DirectX 11 initialize failed-------- \n");
		return false;
	}
	g_SysLog->Log(_INFO, "--------DirectX 11 initialize success-------- \n");

	WinApp.SetParseMsgCallback(gfx.ParseMsgStaticEntry, &gfx);
	return true;
}

bool Engine::ProcessMessages()
{
	return WinApp.ProcessMessages();
}

bool Engine::Update()
{
	KeyboardClass *keyboard = WinApp.mWinMouseKeyboard.GetKeyboard();
	MouseClass *mouse = WinApp.mWinMouseKeyboard.GetMouse();

	if (keyboard->KeyIsPressed(VK_ESCAPE))
	{
		std::vector<WindowInfo> l_info = WinApp.GetWindowInfos();
		PostMessage(l_info[0].handle, WM_CLOSE, 0, 0);
	}
	// Release ALL queue Buffer if no use
	while (!keyboard->CharBufferIsEmpty()) { unsigned char ch = keyboard->ReadChar(); }
	while (!keyboard->KeyBufferIsEmpty()) { KeyboardEvent kbe = keyboard->ReadKey(); }
	while (!mouse->EventBufferIsEmpty()) { MouseEvent me = mouse->ReadEvent(); }

	gfx.Update();
	return true;
}

void Engine::RenderFrame()
{
	static int l_FPSCnt = 0;
	static double l_timeAccmulator = 0;
	static double l_FPS = 0;
	WinApp.timer.TimerStart();
	gfx.Render(l_FPS);
	WinApp.timer.TimerEnd();


	l_timeAccmulator += WinApp.timer.Getms();
	l_FPSCnt++;
	if (l_FPSCnt > 60)
	{
		l_FPS = 1000.0 / (l_timeAccmulator / l_FPSCnt);
		l_timeAccmulator = 0;
		l_FPSCnt = 0;
	}
	
}

void Engine::Release()
{
	gfx.Release();
	if (g_SysLog.get() != nullptr)
	{
		g_SysLog->Log(_INFO, "Finish all release\n");
	}
	
}