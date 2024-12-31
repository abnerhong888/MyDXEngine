#include "GUIScrollBar.h"
using namespace DX11;

/************************************************************************/
/*   GUIScrollBar                                                       */
/************************************************************************/
GUIScrollBar::~GUIScrollBar()
{
	delete mBar;
	delete mBtn;
	delete mBtnU;
	delete mBtnD;
	delete mBtnR;
	delete mBtnL;
}

GUIScrollBar::GUIScrollBar(std::string pName, ScrollBarType pType,
	sptrTexSRV pBtnSRV, sptrTexSRV pBarSRV,
	sptrTexSRV pBtnUSRV, sptrTexSRV pBtnDSRV,
	sptrTexSRV pBtnRSRV, sptrTexSRV pBtnLSRV)
{
	mName = pName;
	mBtnSRV = pBtnSRV;
	mBarSRV = pBarSRV;
	mBtnUSRV = pBtnUSRV;
	mBtnDSRV = pBtnDSRV;
	mBtnRSRV = pBtnRSRV;
	mBtnLSRV = pBtnLSRV;
	mScrollType = pType;
}

void GUIScrollBar::Init()
{
	CalculateRects();

	mBtn = new GUIButton("ScrollBarItem", nullptr, mBtnSRV);
	//Control
	mBtn->SetRect(mBtnRect);
	mBtn->SetViewPort(GetViewPort());
	mBtn->SetRTWSize(GetRTWSize());
	mBtn->SetContinuous(true);
	mBtn->SetFocusMode(false);
	mBtn->SetMoveMode(true, mScrollType == _Hor ? MoveX : MoveY);
	mBtn->SetAnimation(false);
	mBtn->SetControlType(_Button);
	//Static
	mBtn->SetHotKey(0);
	mBtn->SetMKB(GetMKB());
	//Button
	//mBtn->SetText(L"");


	mBar = new GUIButton("ScrollBarItem", nullptr, mBarSRV);
	//Control
	mBar->SetRect(mBarRect);
	mBar->SetViewPort(GetViewPort());
	mBar->SetRTWSize(GetRTWSize());
	mBar->SetContinuous(false);
	mBar->SetFocusMode(false);
	mBar->SetMoveMode(false, NoneMove);
	mBar->SetAnimation(false);
	mBar->SetControlType(_Button);
	//Static
	mBar->SetHotKey(0);
	mBar->SetMKB(GetMKB());
	//Button
	//mBar->SetText(L"");


	if (mScrollType == _Hor)
	{
		mBtnR = new GUIButton("ScrollBarItem", nullptr, mBtnRSRV);
		//Control
		mBtnR->SetRect(mBtnRRect);
		mBtnR->SetViewPort(GetViewPort());
		mBtnR->SetRTWSize(GetRTWSize());
		mBtnR->SetContinuous(false);
		mBtnR->SetFocusMode(false);
		mBtnR->SetMoveMode(false, NoneMove);
		mBtnR->SetAnimation(false);
		mBtnR->SetControlType(_Button);
		//Static
		mBtnR->SetHotKey(0);
		mBtnR->SetMKB(GetMKB());
		//Button
		//mBtnR->SetText(L"");


		mBtnL = new GUIButton("ScrollBarItem", nullptr, mBtnLSRV);
		//Control
		mBtnL->SetRect(mBtnLRect);
		mBtnL->SetViewPort(GetViewPort());
		mBtnL->SetRTWSize(GetRTWSize());
		mBtnL->SetContinuous(false);
		mBtnL->SetFocusMode(false);
		mBtnL->SetMoveMode(false, NoneMove);
		mBtnL->SetAnimation(false);
		mBtnL->SetControlType(_Button);
		//Static
		mBtnL->SetHotKey(0);
		mBtnL->SetMKB(GetMKB());
		//Button
		//mBtnL->SetText(L"");
	}
	else if (mScrollType == _Ver)
	{
		mBtnU = new GUIButton("ScrollBarItem", nullptr, mBtnUSRV);
		//Control
		mBtnU->SetRect(mBtnURect);
		mBtnU->SetViewPort(GetViewPort());
		mBtnU->SetRTWSize(GetRTWSize());
		mBtnU->SetContinuous(false);
		mBtnU->SetFocusMode(false);
		mBtnU->SetMoveMode(false, NoneMove);
		mBtnU->SetAnimation(false);
		mBtnU->SetControlType(_Button);
		//Static
		mBtnU->SetHotKey(0);
		mBtnU->SetMKB(GetMKB());
		//Button
		//mBtnU->SetText(L"");


		mBtnD = new GUIButton("ScrollBarItem", nullptr, mBtnDSRV);
		//Control
		mBtnD->SetRect(mBtnDRect);
		mBtnD->SetViewPort(GetViewPort());
		mBtnD->SetRTWSize(GetRTWSize());
		mBtnD->SetContinuous(false);
		mBtnD->SetFocusMode(false);
		mBtnD->SetMoveMode(false, NoneMove);
		mBtnD->SetAnimation(false);
		mBtnD->SetControlType(_Button);
		//Static
		mBtnD->SetHotKey(0);
		mBtnD->SetMKB(GetMKB());
		//Button
		//mBtnD->SetText(L"");

	}
}
void GUIScrollBar::CalculateRects()
{
	if (mScrollType == _Hor)
	{
		mBtnLRect = MT::float4(mRect.rx, mRect.ry, mRect.rh, mRect.rh);
		mBtnRRect = MT::float4(mRect.rx + mRect.rw - mRect.rh, mRect.ry, mRect.rh, mRect.rh);
		mBarRect = MT::float4(mRect.rx + mBtnLRect.rw, mRect.ry, mRect.rw - (mBtnLRect.rw + mBtnRRect.rw), mRect.rh);
		mBtnRect = MT::float4(mBarRect.rx, mRect.ry, mRect.rh, mRect.rh);
	}
	else if (mScrollType == _Ver)
	{
		mBtnURect = MT::float4(mRect.rx, mRect.ry, mRect.rw, mRect.rw);
		mBtnDRect = MT::float4(mRect.rx, mRect.ry + mRect.rh - mRect.rw, mRect.rw, mRect.rw);
		mBarRect = MT::float4(mRect.rx, mRect.ry + mBtnURect.rh, mRect.rw, mRect.rh - (mBtnURect.rh + mBtnDRect.rh));
		mBtnRect = MT::float4(mRect.rx, mBarRect.ry, mRect.rw, mRect.rw);
	}
}

void GUIScrollBar::ObjectMove()
{
	if (isMoveMode)
	{
		CalculateRects();

		if (mScrollType == _Hor)
		{
			mBtnR->SetRect(mBtnRRect);
			mBtnL->SetRect(mBtnLRect);
		}
		else if (mScrollType == _Ver)
		{
			mBtnU->SetRect(mBtnURect);
			mBtnD->SetRect(mBtnDRect);
		}
		mBtn->SetRect(mBtnRect);
		mBar->SetRect(mBarRect);

		SetRng(mRng);
	}
}

void GUIScrollBar::CheckBtnValueState()
{
	MT::float4 *l_BtnRect = mBtn->GetRectPtr();
	if (mScrollType == _Hor)
	{
		l_BtnRect->rx = min(l_BtnRect->rx, mBtnRng.Max);
		l_BtnRect->rx = max(l_BtnRect->rx, mBtnRng.Min);
		mCurrentVal = (l_BtnRect->rx - mBtnRng.Min) / mBtnUnit;
	}
	else if (mScrollType == _Ver)
	{
		l_BtnRect->ry = min(l_BtnRect->ry, mBtnRng.Max);
		l_BtnRect->ry = max(l_BtnRect->ry, mBtnRng.Min);
		mCurrentVal = (l_BtnRect->ry - mBtnRng.Min) / mBtnUnit;
	}

	if (mPreVal != mCurrentVal)
	{
		mDiffVal = mPreVal - mCurrentVal;
		mPreVal = mCurrentVal;
		mIsValChange = true;
	}
}

void GUIScrollBar::SetIncrease()
{
	MT::float4 *l_BtnRect = mBtn->GetRectPtr();
	if (mScrollType == _Hor) { l_BtnRect->rx += mBtnRng.Stp; }
	else if (mScrollType == _Ver) { l_BtnRect->ry += mBtnRng.Stp; }
	CheckBtnValueState();
}

void GUIScrollBar::SetDecrease()
{
	MT::float4 *l_BtnRect = mBtn->GetRectPtr();
	if (mScrollType == _Hor) { l_BtnRect->rx -= mBtnRng.Stp; }
	else if (mScrollType == _Ver) { l_BtnRect->ry -= mBtnRng.Stp; }
	CheckBtnValueState();
}
void GUIScrollBar::CheckEvented()
{
	if (!isEnable) return;
	GUIStatic::CheckEvented();
	this->ObjectMove();

	mBtn->CheckEvented();
	mBar->CheckEvented();
	if (isMoveMode) return;

	if (mBtn->GetEvented() || mBtn->GetMouseOn())
	{
		mBar->SetEvented(false);
		mBar->SetClickDown(false);
		mBar->SetMouseHold(false);
		mBar->SetMouseOn(false);
	}

	MT::float4 *l_BtnRect = mBtn->GetRectPtr();
	if (mScrollType == _Hor)
	{
		mBtnL->CheckEvented();
		mBtnR->CheckEvented();
		if (mBtnL->GetEvented()) { l_BtnRect->rx -= mBtnRng.Stp; }
		if (mBtnR->GetEvented()) { l_BtnRect->rx += mBtnRng.Stp; }
		if (IsWheelUp()) l_BtnRect->rx -= mBtnRng.Stp;
		if (IsWheelDown()) l_BtnRect->rx += mBtnRng.Stp;
		if (mBar->GetEvented())
		{
			if (GetMousePosVp().x < l_BtnRect->rx)
				l_BtnRect->rx -= mBtnRng.BigStp;
			else
				l_BtnRect->rx += mBtnRng.BigStp;
		}
	}
	else if (mScrollType == _Ver)
	{
		mBtnU->CheckEvented();
		mBtnD->CheckEvented();
		if (mBtnU->GetEvented()) { l_BtnRect->ry -= mBtnRng.Stp; }
		if (mBtnD->GetEvented()) { l_BtnRect->ry += mBtnRng.Stp; }
		if (IsWheelUp()) l_BtnRect->ry -= mBtnRng.Stp;
		if (IsWheelDown()) l_BtnRect->ry += mBtnRng.Stp;
		if (mBar->GetEvented())
		{
			if (GetMousePosVp().y < l_BtnRect->ry)
				l_BtnRect->ry -= mBtnRng.BigStp;
			else
				l_BtnRect->ry += mBtnRng.BigStp;
		}
	}
	CheckBtnValueState();
}

void GUIScrollBar::Render()
{
	if (!isEnable) return;

	RenderTool::SetBlend(AlphaBlend);

	RenderTool::SetViewPort(mRect);

	mBar->Render();
	mBtn->Render();
	if (mScrollType == _Hor)
	{
		mBtnL->Render();
		mBtnR->Render();
	}
	else if (mScrollType == _Ver)
	{
		mBtnU->Render();
		mBtnD->Render();
	}
	RenderTool::SetBlend(NullState);
}

void GUIScrollBar::SetRng(UIRng pRng)
{
	MT::float4 *l_BtnRect = mBtn->GetRectPtr();
	MT::float4 l_BarRect = mBar->GetRect();

	mRng = pRng;
	mCurrentVal = mRng.Def;
	float l_BtnSize = 35.0;
	mBtnUnit = (mScrollType == _Hor ? l_BarRect.rw - l_BtnSize : l_BarRect.rh - l_BtnSize) / (pRng.Max - pRng.Min);
	mBtnRng.Min = (mScrollType == _Hor ? l_BarRect.rx : l_BarRect.ry);
	mBtnRng.Max = mBtnRng.Min + (mScrollType == _Hor ? l_BarRect.rw : l_BarRect.rh) - l_BtnSize;

	mBtnRng.Stp = (mBtnUnit * pRng.Stp);
	mBtnRng.BigStp = mBtnRng.Stp * pRng.BigStp;
	mBtnRng.Def = pRng.Def * pRng.Stp;

	mBtnRng.Def = mBtnRng.Min + (mBtnRng.Def * mBtnUnit);

	mScrollType == _Hor ? l_BtnRect->rw = l_BtnSize : l_BtnRect->rh = l_BtnSize;
	mScrollType == _Hor ? l_BtnRect->rx = (mBtnRng.Def) : l_BtnRect->ry = (mBtnRng.Def);

}
UIRng GUIScrollBar::GetRng()
{
	return mRng;
}

float GUIScrollBar::GetCurrentVal()
{
	return mCurrentVal;
}

float GUIScrollBar::GetDiffVal()
{
	return mDiffVal;
}

float GUIScrollBar::GetIsValChagne()
{
	if (mIsValChange) { mIsValChange = false; return true; }
	return false;
}