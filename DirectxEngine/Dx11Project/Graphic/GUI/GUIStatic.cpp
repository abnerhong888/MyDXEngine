#include "GUIStatic.h"

using namespace DX11;

/************************************************************************/
/* GUIControl                                                           */
/************************************************************************/

/************************************************************************/
/*   GUIStatic                                                          */
/************************************************************************/

bool GUIStatic::GetEvented()
{
	if (isMouseEvented || isKeyEvented)
	{
		if (!isContinuous && !isFocusMode) isMouseEvented = isKeyEvented = false;
		return true;
	}
	return false;
}
void GUIStatic::SetEvented(bool pFlag)
{
	isMouseEvented = isKeyEvented = pFlag;
}

bool GUIStatic::isOnRect(MT::float2 pMousePosVp)
{
	if (pMousePosVp.x >= mRect.rx + mOnRectOffset.x &&
		pMousePosVp.x <= mRect.rx + mRect.rw + mOnRectOffset.x&&
		pMousePosVp.y >= mRect.ry + mOnRectOffset.y &&
		pMousePosVp.y <= mRect.ry + mRect.rh + mOnRectOffset.y)
	{
		return true;
	}
	return false;
}

bool GUIStatic::isMouseOnRect()
{
	if (isOnRect(GetMousePosVp())) return true;
	return false;
}

bool GUIStatic::isClickDown()
{
	MouseClass *l_m = mMKB->GetMouse();
	if (l_m->IsLeftDown())
	{
		if (isOnRect(GetMousePosVp())) return true;
	}
	return false;
}

bool GUIStatic::isClickUp()
{
	MouseClass *l_m = mMKB->GetMouse();
	if (!l_m->IsLeftDown())
	{
		if (isOnRect(GetMousePosVp()))
		{
			return true;
		}
	}
	return false;
}
bool GUIStatic::isJustClick()
{
	MouseClass *l_m = mMKB->GetMouse();
	if (!l_m->IsLeftDown()) return true;
	return false;
}
bool GUIStatic::isHotKeyDown()
{
	KeyboardClass *l_kb = mMKB->GetKeyboard();
	if (l_kb->KeyIsPressed(mHotKey)) return true;
	return false;
}

bool GUIStatic::isHotKeyUp()
{
	KeyboardClass *l_kb = mMKB->GetKeyboard();
	if (!l_kb->KeyIsPressed(mHotKey)) return true;
	return false;
}

bool GUIStatic::IsWheelUp()
{
	if (isMouseOnRect())
	{
		MouseClass *l_m = mMKB->GetMouse();
		if (l_m->IsWheelUp()) return true;
	}
	return false;
}
bool GUIStatic::IsWheelDown()
{
	if (isMouseOnRect())
	{
		MouseClass *l_m = mMKB->GetMouse();
		if (l_m->IsWheelDown()) return true;
	}
	return false;
}
MT::float2 GUIStatic::GetMousePosVp()
{
	MouseClass *l_m = mMKB->GetMouse();
	MT::float2 pos;
	pos.x = (l_m->GetPosX() * (mViewport->rw / mRTWSize->w)) - mViewport->rx;
	pos.y = (l_m->GetPosY() * (mViewport->rh / mRTWSize->h)) - mViewport->ry;
	return pos;
}

void GUIStatic::CheckEvented()
{
	if (!isEnable) return;
	if (!isFocusMode)
	{
		if (isClickUp() && isMouseHold) { isMouseDown = false; isMouseHold = false; isMouseEvented = isContinuous ? false : true; }
		else { isMouseDown = false; isMouseHold = false; isMouseEvented = isContinuous ? false : false; }

		if (isHotKeyUp() && isKeyHold) { isKeyDown = false; isKeyHold = false; isKeyEvented = isContinuous ? false : true; }
		else { isKeyDown = false; isKeyHold = false; isKeyEvented = isContinuous ? false : false; }

		if (isClickDown()) { isMouseDown = true; isMouseHold = true; isMouseEvented = isContinuous ? true : false; }

		if (isHotKeyDown()) { isKeyDown = true; isKeyHold = true; isKeyEvented = isContinuous ? true : false; }
	}
	else
	{
		if (isClickUp() && isMouseHold) { isMouseDown = false; isMouseEvented = !isMouseEvented; isMouseHold = false; }
		if (isClickDown()) { isMouseDown = true; isMouseHold = true; }

		if (isHotKeyUp() && isKeyHold) { isKeyDown = false; isMouseEvented = !isMouseEvented; isKeyHold = false; }
		if (isHotKeyDown()) { isKeyDown = true; isKeyHold = true; }

	}
	if (isMouseOnRect()) isMouseOn = true; else isMouseOn = false;

	MoveCalculate();

}

void GUIStatic::MoveCalculate()
{
	if (isMoveMode)
	{
		if (isMouseEvented)
		{
			MT::float2 pos = this->GetMousePosVp();

			if (mMoveType == MoveX || mMoveType == MoveXY)
			{
				if (!MoveflagX) { MoveClickposX = (pos.x - mRect.rx); MoveflagX = true; }
				else { mRect.rx = pos.x - MoveClickposX; }
			}
			if (mMoveType == MoveY || mMoveType == MoveXY)
			{
				if (!MoveflagY) { MoveClickposY = (pos.y - mRect.ry); MoveflagY = true; }
				else { mRect.ry = pos.y - MoveClickposY; }
			}
		}
		else
		{
			if (mMoveType == MoveX || mMoveType == MoveXY) MoveflagX = false;
			if (mMoveType == MoveY || mMoveType == MoveXY) MoveflagY = false;
		}
	}
}