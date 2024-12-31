#ifndef __WINDOWSAPPLICATION_H__
#define __WINDOWSAPPLICATION_H__

#include "BaseHeader.h"
#include "Resource.h"
#include "Common.h"

class WindowsApplication
{
public:
	WindowsApplication();
	~WindowsApplication();
	std::vector<WindowInfo> GetWindowInfos();
	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	bool CheckProcessExist(std::wstring pProcessName);
	void SetParseMsgCallback(ParseMsgCallback pEntry, void* pUserdata);

	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	MyTimer timer;
	MouseKeyBoard mWinMouseKeyboard;
protected:

	bool CreateWindows(WindowInfo *pWindowInfo);
private:

	ParseMsgCallback mParseMsgCallback = nullptr;
	void* mMsgUserdata = nullptr;

	void RegisterWindowsClass();
	HINSTANCE hInstance = NULL; 
	std::vector<WindowInfo> mWinInfos;
	std::string window_title = "";
	std::wstring window_title_wide = L""; 
	std::string window_class = "";
	std::wstring window_class_wide = L"";
};

#endif