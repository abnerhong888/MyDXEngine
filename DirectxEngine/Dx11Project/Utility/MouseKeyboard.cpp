#include "MouseKeyboard.h"
#include <memory>

MouseKeyBoard::MouseKeyBoard()
{

}

bool MouseKeyBoard::ParseEvent(MouseKeyBoard *pMouseKeyboard, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		pMouseKeyboard->KeyDownMSG(wParam, lParam); return true;
	case WM_KEYUP:
		pMouseKeyboard->KeyUpMSG(wParam, lParam); return true;
	case WM_CHAR:
		pMouseKeyboard->KeyCharMSG(pMouseKeyboard, wParam, lParam); return true;
	case WM_MOUSEWHEEL:
		pMouseKeyboard->MouseWheelMSG(wParam, lParam); return true;
	case WM_LBUTTONUP:
		pMouseKeyboard->LButtonUpMSG(wParam, lParam); return true;
	case WM_LBUTTONDOWN:
		pMouseKeyboard->LButtonDownMSG(wParam, lParam); return true;
	case WM_RBUTTONUP:
		pMouseKeyboard->RButtonUpMSG(wParam, lParam); return true;
	case WM_RBUTTONDOWN:
		pMouseKeyboard->RButtonDownMSG(wParam, lParam); return true;
	case WM_MBUTTONUP:
		pMouseKeyboard->MButtonUpMSG(wParam, lParam); return true;
	case WM_MBUTTONDOWN:
		pMouseKeyboard->MButtonDownMSG(wParam, lParam); return true;
	case WM_MOUSEMOVE:
		pMouseKeyboard->MouseMoveMSG(wParam, lParam); return true;
	case WM_INPUT:
		pMouseKeyboard->MouseRowInputMSG(pMouseKeyboard, wParam, lParam); 
		//Need to call DefWindowProc for WM_INPUT messages
		DefWindowProc(hwnd, uMsg, wParam, lParam);
		return true;
	}

	return false;
}

MouseClass *MouseKeyBoard::GetMouse()
{
	return &mMouseClass;
}

KeyboardClass *MouseKeyBoard::GetKeyboard()
{
	return &mKeyBoardClass;
}

void MouseKeyBoard::KeyDownMSG(WPARAM wParam, LPARAM lParam)
{
	unsigned char keycode = static_cast<unsigned char>(wParam);
	if (mKeyBoardClass.IsKeysAutoRepeat())
	{
		mKeyBoardClass.OnKeyPressed(keycode);
	}
	else
	{
		const bool wasPressed = lParam & 0x40000000;
		if (!wasPressed)
		{
			mKeyBoardClass.OnKeyPressed(keycode);
		}
	}
}

void MouseKeyBoard::KeyUpMSG(WPARAM wParam, LPARAM lParam)
{
	unsigned char keycode = static_cast<unsigned char>(wParam);
	mKeyBoardClass.OnKeyReleased(keycode);
}

void MouseKeyBoard::KeyCharMSG(MouseKeyBoard *pMouseKeyboard, WPARAM wParam, LPARAM lParam)
{
	unsigned char ch = static_cast<unsigned char>(wParam);
	if (pMouseKeyboard->GetKeyboard()->IsCharsAutoRepeat())
	{
		pMouseKeyboard->GetKeyboard()->OnChar(ch);
	}
	else
	{
		const bool wasPressed = lParam & 0x40000000;
		if (!wasPressed)
		{
			pMouseKeyboard->GetKeyboard()->OnChar(ch);
		}
	}
}

void MouseKeyBoard::MouseMoveMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	mMouseClass.OnMouseMove(x, y);
}

void MouseKeyBoard::LButtonDownMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	mMouseClass.OnLeftPressed(x, y);
}

void MouseKeyBoard::LButtonUpMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	mMouseClass.OnLeftReleased(x, y);
}

void MouseKeyBoard::RButtonDownMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	mMouseClass.OnRightPressed(x, y);
}

void MouseKeyBoard::RButtonUpMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	mMouseClass.OnRightReleased(x, y);
}

void MouseKeyBoard::MButtonDownMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	mMouseClass.OnMiddlePressed(x, y);
}

void MouseKeyBoard::MButtonUpMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	mMouseClass.OnMiddleReleased(x, y);
}

void MouseKeyBoard::MouseWheelMSG(WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
	{
		mMouseClass.OnWheelUp(x, y);
	}
	else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
	{
		mMouseClass.OnWheelDown(x, y);
	}

}

void MouseKeyBoard::MouseRowInputMSG(MouseKeyBoard *pMouseKeyboard, WPARAM wParam, LPARAM lParam)
{
	UINT dataSize;
	GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER)); //Need to populate data size first

	if (dataSize > 0)
	{
		std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
		if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
		{
			RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
			if (raw->header.dwType == RIM_TYPEMOUSE)
			{
				pMouseKeyboard->GetMouse()->OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
			}
		}
	}
}