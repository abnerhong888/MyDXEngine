#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "ErrorLogger.h"
#include "FileSystem.h"
#include "MyTimer.h"
#include "MyTypes.h"
#include "SmartPointer.h"
#include "StringConverter.h"
#include "MouseKeyboard.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

#define Quote_It( It )  #It
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x) { x->Release(); x = NULL; } 
#endif

#define SAFE_DELETE(x) if(x) {delete x; x = nullptr;}
#define SAFE_FREE(x) if(x) {free(x); x = nullptr;}

#include <iostream>
#include <string>
#include <typeinfo>
#define D_MATH_PI 3.14159265359
#define D_DEG2RAD(deg) ( static_cast<decltype(deg)>(D_MATH_PI / 180.0) * (deg)  )
#define D_RAD2DEG(rad) ( static_cast<decltype(rad)>(180.0 / D_MATH_PI) * (rad)  )
#define D_GetVarName(_var) #_var
#define D_GetTypeName(_var) typeid(_var).name()

// parse mouse keyboard message callback 
typedef void(*ParseMsgCallback)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, void *userdata);

typedef struct WindowInfo
{
	HWND handle;
	MT::int4 rect;
	MT::int2 size;
	WindowInfo() { ZeroMemory(this, sizeof(WindowInfo)); }
	WindowInfo(int _x, int _y, int _width, int _height)
		:handle(nullptr), size(_width, _height), rect(_x, _y, _width, _height) {}
	WindowInfo &operator = (WindowInfo &in) { memcpy(this, &in, sizeof(WindowInfo)); return *this; }

}WindowInfo;

#endif