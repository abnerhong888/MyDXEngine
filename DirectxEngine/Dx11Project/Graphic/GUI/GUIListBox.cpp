#include "GUIListBox.h"
using namespace DX11;

/************************************************************************/
/*   GUIListBox                                                         */
/************************************************************************/
GUIListBox::~GUIListBox()
{
	delete mScrollBar;
	for (std::pair<int, GUIButton*> btn : mItems)
	{
		delete btn.second;
	}
	if (mItems.size() > 0) mItems.clear();
}

GUIListBox::GUIListBox(std::string pName, sptrTexSRV pBackSRV, sptrTexSRV pScrollBtnSRV, sptrTexSRV pScrollBtnUpSRV, sptrTexSRV pScrollDownSRV)
{
	mName = pName;
	mBackSRV = pBackSRV;
	mScrollBtnSRV = pScrollBtnSRV;
	mScrollBtnUpSRV = pScrollBtnUpSRV;
	mScrollDownSRV = pScrollDownSRV;
}

void GUIListBox::Init()
{
	CalculateRects();

	mBackRTV = RTVTool::CreateRTV("mBackRTV", (int)mBackRect.rw, (int)mBackRect.rh, RENDER_SRV_TARGET, RGBA8_U);

	mScrollBar = new GUIScrollBar("ListBoxItem", _Ver,
		mScrollBtnSRV, nullptr,
		mScrollBtnUpSRV, mScrollDownSRV,
		nullptr, nullptr
	);

	//Control
	mScrollBar->SetRect(mScrollBarRect);
	mScrollBar->SetViewPort(GetViewPort());
	mScrollBar->SetRTWSize(GetRTWSize());
	mScrollBar->SetContinuous(false);
	mScrollBar->SetFocusMode(false);
	mScrollBar->SetMoveMode(false, NoneMove);
	mScrollBar->SetAnimation(false);
	mScrollBar->SetControlType(_ScrollBar);
	//Static
	mScrollBar->SetHotKey(0);
	mScrollBar->SetMKB(GetMKB());
	//ScrollBar
	mScrollBar->Init();

}

void GUIListBox::CalculateRects()
{
	mScrollBarRect = MT::float4(mRect.rx + mRect.rw - 30.f, mRect.ry, 30.f, mRect.rh);
	mBackRect = MT::float4(mRect.rx, mRect.ry, mRect.rw - 30.f, mRect.rh);
}

void GUIListBox::ObjectMove()
{
	if (isMoveMode)
	{
		CalculateRects();
		mScrollBar->SetRect(mScrollBarRect);
		mScrollBar->SetMoveMode(GetMoveMode(), GetMoveType());
		mScrollBar->ObjectMove();

		for (std::pair<int, GUIButton*> item : mItems)
		{
			item.second->SetOnRectOffset(MT::float2(mRect.x, mRect.y));
		}
	}
	else
	{
		if (mScrollBar->GetMoveMode())
			mScrollBar->SetMoveMode(GetMoveMode(), GetMoveType());
	}
}

void GUIListBox::CheckEvented()
{
	if (!isEnable) return;
	GUIStatic::CheckEvented();
	this->ObjectMove();

	mScrollBar->CheckEvented();

	for (int i = 0; i < mItems.size(); i++)
	{
		MT::float4 *l_rect = mItems[i]->GetRectPtr();
		if (l_rect->ry < -mItemHeight) { i = (int)(std::abs(l_rect->ry / mItemHeight)) - 1; continue; }

		if (l_rect->ry + l_rect->rh <= (0.0f + mBackRect.rh + mItemHeight) && l_rect->ry >= 0.0f - mItemHeight)
		{
			mItems[i]->CheckEvented();
			if (mItems[i]->GetEvented()) { mSelectedIdx = i; mIsSelected = true; }
		}
		else if (l_rect->ry + l_rect->rh >= (0.0f + mBackRect.rh + mItemHeight)) { break; }
	}

	if (isMoveMode) return;


	if (IsWheelDown()) { mScrollBar->SetIncrease(); }
	if (IsWheelUp()) { mScrollBar->SetDecrease(); }

	if (mScrollBar->GetIsValChagne())
	{
		for (int i = 0; i < mItems.size(); i++)
		{
			MT::float4 *l_rect = mItems[i]->GetRectPtr();
			l_rect->ry = (mItemHeight * i) - (int)(mItemHeight * mScrollBar->GetCurrentVal());
		}
	}

}

void GUIListBox::Render()
{
	if (!isEnable) return;

	mScrollBar->Render();

	RTVTool::SetRenderTargetView(mBackRTV);
	RenderTool::SetViewPort(0.0f, 0.0f, mBackRect.rw, mBackRect.rh);

	RenderTool::SetBlend(AlphaBlend);
	if (mBackSRV)
		RenderTool::Plane(LinearWarp, mBackSRV);
	else
		RenderTool::PlaneColor(LinearWarp, RoyalBlue, 1.0f);

	for (int i = 0; i < mItems.size(); i++)
	{
		MT::float4 *l_rect = mItems[i]->GetRectPtr();
		if (l_rect->ry < -mItemHeight) { i = (int)(std::abs(l_rect->ry / mItemHeight)) - 1; continue; }

		if (l_rect->ry + l_rect->rh <= (0.0f + mBackRect.rh + mItemHeight) && l_rect->ry >= 0.0f - mItemHeight)
		{
			mItems[i]->Render();
		}
		else if (l_rect->ry + l_rect->rh >= (0.0f + mBackRect.rh + mItemHeight)) { break; }
	}

	RTVTool::SetRenderTargetView(GetRTV(), false);
	RenderTool::SetViewPort(mBackRect);
	RenderTool::SetBlend(AlphaBlend);
	RenderTool::Plane(LinearWarp, mBackRTV->GetSRV());
	RenderTool::SetBlend(NullState);
}

void GUIListBox::SetItems(std::vector<std::pair<int, std::wstring>> pItems)
{
	float l_btnH = 0.0f;
	for (std::pair<int, std::wstring> item : pItems)
	{
		GUIButton *l_Btn = new GUIButton("ListBoxItem", nullptr, nullptr);

		mItems[item.first] = l_Btn;

		MT::float4 l_btnRect(10.f, l_btnH, mRect.rw - mScrollBarRect.rw - 20.f, mItemHeight);
		l_btnH += mItemHeight;

		//Control
		l_Btn->SetRect(l_btnRect);

		l_Btn->SetViewPort(GetViewPort());
		l_Btn->SetRTWSize(GetRTWSize());
		l_Btn->SetContinuous(false);
		l_Btn->SetFocusMode(false);
		l_Btn->SetMoveMode(false, NoneMove);
		l_Btn->SetAnimation(true);
		l_Btn->SetControlType(_Button);
		//Static
		l_Btn->SetHotKey(0);
		l_Btn->SetMKB(GetMKB());
		l_Btn->SetOnRectOffset(MT::float2(mRect.x, mRect.y));
		//Button
		l_Btn->SetText(item.second);
	}
	UIRng l_Rng(0, 1, mItems.size() / 10.0f, 0, (float)mItems.size() - 1.0f);
	mScrollBar->SetRng(l_Rng);
}

bool GUIListBox::GetIsSelected()
{
	if (mIsSelected) { mIsSelected = false; return true; }
	return false;
}