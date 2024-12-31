
#include "WindowsApplication.h"


WindowsApplication::WindowsApplication()
{
	static bool raw_input_initialized = false;
	if (raw_input_initialized == false)
	{
		RAWINPUTDEVICE rid;

		rid.usUsagePage = 0x01; //Mouse
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = NULL;

		if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
		{
			ErrorLogger::MsgBoxLog(GetLastError(), "Failed to register raw input devices.");
			exit(-1);
		}

		raw_input_initialized = true;
	}
}

std::vector<WindowInfo> WindowsApplication::GetWindowInfos()
{
	return mWinInfos;
}

bool WindowsApplication::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	this->hInstance = hInstance;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class); 

	RegisterWindowsClass();

	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
	
	WindowInfo l_MainWinInfo(centerScreenX, centerScreenY, width, height);
	RECT l_rect = { l_MainWinInfo.rect.rx, l_MainWinInfo.rect.ry, l_MainWinInfo.rect.rw, l_MainWinInfo.rect.rh };
	AdjustWindowRect(&l_rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU/*WS_POPUP*/ , FALSE);
	CreateWindows(&l_MainWinInfo);
	ShowWindow(l_MainWinInfo.handle, SW_SHOW);
	SetForegroundWindow(l_MainWinInfo.handle);
	SetFocus(l_MainWinInfo.handle);
	mWinInfos.emplace_back(l_MainWinInfo);

	return true;
}

bool WindowsApplication::CreateWindows(WindowInfo *pWindowInfo)
{
	pWindowInfo->handle = CreateWindowExW(0,
		this->window_class_wide.c_str(),
		this->window_title_wide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU/*WS_POPUP*/,
		pWindowInfo->rect.rx,
		pWindowInfo->rect.ry,
		pWindowInfo->rect.rw + 14,
		pWindowInfo->rect.rh + 38,
		NULL,
		NULL,
		this->hInstance,
		this); //Param to create window

	if (pWindowInfo->handle == nullptr)
	{
		ErrorLogger::MsgBoxLog(GetLastError(), "CreateWindowEX Failed for window: " + this->window_title);
		return false;
	}
	return true;
}

bool WindowsApplication::ProcessMessages()
{
	
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); 
	
	while (PeekMessage(&msg,
		mWinInfos[0].handle,
		0,    
		0,    
		PM_REMOVE))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}

	// Check if the window was closed
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(mWinInfos[0].handle))
		{
			mWinInfos[0].handle = NULL;
			UnregisterClassW(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}

WindowsApplication::~WindowsApplication()
{
	if (mWinInfos[0].handle != NULL)
	{
		UnregisterClassW(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(mWinInfos[0].handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// All other messages
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	default:
	{
		// retrieve ptr to window class
		WindowsApplication* const pWindow = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

static LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowsApplication * pWindow = reinterpret_cast<WindowsApplication*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) //Sanity check
		{
			ErrorLogger::MsgBoxLog("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	
}

void WindowsApplication::RegisterWindowsClass()
{
	WNDCLASSEXW wc; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hInstance = this->hInstance; 
	wc.hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_DX11PROJECT));;
	wc.hIconSm = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);;
	wc.lpszMenuName = NULL; 
	wc.lpszClassName = this->window_class_wide.c_str(); 
	wc.cbSize = sizeof(WNDCLASSEX); 
	RegisterClassExW(&wc); 
}

LRESULT WindowsApplication::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (mParseMsgCallback) mParseMsgCallback(hwnd, uMsg, wParam, lParam, mMsgUserdata);

	MouseKeyBoard::ParseEvent(&mWinMouseKeyboard, hwnd, uMsg, wParam, lParam);
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

bool WindowsApplication::CheckProcessExist(std::wstring pProcessName)
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, pProcessName.c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		std::wstring msg = pProcessName + L" Already Exist !";
		MessageBoxW(NULL, msg.c_str(), pProcessName.c_str(), MB_OK + MB_ICONWARNING);
		ReleaseMutex(hMutex);
		return true;
		//exit(0);
	}
	return false;
}

void WindowsApplication::SetParseMsgCallback(ParseMsgCallback pEntry, void* pUserdata)
{
	mParseMsgCallback = pEntry;
	mMsgUserdata = pUserdata;
}