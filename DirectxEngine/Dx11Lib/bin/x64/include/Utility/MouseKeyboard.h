#ifndef __MouseKeyboard_H__
#define __MouseKeyboard_H__

#include "KeyboardClass.h"
#include "MouseClass.h"
#include "windows.h"

class MouseKeyBoard
{
public:
	MouseKeyBoard();
	static bool ParseEvent(MouseKeyBoard *pMouseKeyboard, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	MouseClass *GetMouse();
	KeyboardClass *GetKeyboard();
protected:
	void KeyDownMSG(WPARAM wParam, LPARAM lParam);
	void KeyUpMSG(WPARAM wParam, LPARAM lParam);
	void KeyCharMSG(MouseKeyBoard *pMouseKeyboard, WPARAM wParam, LPARAM lParam);
	void MouseMoveMSG(WPARAM wParam, LPARAM lParam);
	void LButtonDownMSG(WPARAM wParam, LPARAM lParam);
	void LButtonUpMSG(WPARAM wParam, LPARAM lParam);
	void RButtonDownMSG(WPARAM wParam, LPARAM lParam);
	void RButtonUpMSG(WPARAM wParam, LPARAM lParam);
	void MButtonDownMSG(WPARAM wParam, LPARAM lParam);
	void MButtonUpMSG(WPARAM wParam, LPARAM lParam);
	void MouseWheelMSG(WPARAM wParam, LPARAM lParam);
	void MouseRowInputMSG(MouseKeyBoard *pMouseKeyboard, WPARAM wParam, LPARAM lParam);
private:
	MouseClass mMouseClass;
	KeyboardClass mKeyBoardClass;
};

#endif 
