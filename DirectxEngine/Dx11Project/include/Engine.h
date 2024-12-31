#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "WindowsApplication.h"
#include "Graphic/Graphic.h"

class Engine
{
public:
	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	bool Update();
	void RenderFrame();
	void Release();
protected:
	
private:
	DX11::Graphics gfx;
	WindowsApplication WinApp;
};

#endif //__ENGINE_H__