#include "GUIComBox.h"

using namespace DX11;

/************************************************************************/
/* GUIComBox                                                            */
/************************************************************************/

GUIComBox::~GUIComBox()
{
	delete mComBox;
	delete mBtn;
	delete mListBox;
};

GUIComBox::GUIComBox(std::string pName, sptrTexSRV pBtnSRV, sptrTexSRV pComBoxSRV,
	sptrTexSRV pListBoxBackSRV, sptrTexSRV pListBoxScrollBtnSRV,
	sptrTexSRV pListBoxScrollBtnUpSRV, sptrTexSRV pListBoxScrollDownSRV)
{
	mName = pName;
	mBtnSRV = pBtnSRV;
	mComBoxSRV = pComBoxSRV;

	mLB_BackSRV = pListBoxBackSRV;
	mLB_ScrollBtnSRV = pListBoxScrollBtnSRV;
	mLB_ScrollBtnUpSRV = pListBoxScrollBtnUpSRV;
	mLB_ScrollDownSRV = pListBoxScrollDownSRV;
}

void GUIComBox::CalculateRects()
{
	mComBoxRect = MT::float4(mRect.rx, mRect.ry, mRect.rw - mRect.rw / 9, mRect.rh);
	mBtnRect = MT::float4(mRect.rx + mRect.rw - mRect.rw / 10, mRect.ry, mRect.rw / 10, mRect.rh);
	mListBoxRect = MT::float4(mRect.rx, mRect.ry + mRect.rh, mRect.rw - mRect.rw / 9, mListBoxHeight);
}

void GUIComBox::Init()
{
	CalculateRects();

	mListBox = new GUIListBox(
		"ComBoxItem",
		mLB_BackSRV ? mLB_BackSRV : nullptr,
		mLB_ScrollBtnSRV,
		mLB_ScrollBtnUpSRV,
		mLB_ScrollDownSRV);


	//Control
	mListBox->SetRect(mListBoxRect);
	mListBox->SetViewPort(GetViewPort());
	mListBox->SetRTWSize(GetRTWSize());
	mListBox->SetContinuous(false);
	mListBox->SetFocusMode(false);
	mListBox->SetMoveMode(false, NoneMove);
	mListBox->SetAnimation(false);
	mListBox->SetControlType(_ListBox);
	mListBox->SetRTV(GetRTV());
	//Static
	mListBox->SetHotKey(0);
	mListBox->SetMKB(GetMKB());
	//ListBox
	mListBox->Init();
	mListBox->SetItemHeight(mRect.rh);
	//mListBox->SetItems(pItems);

	mComBox = new GUIButton("ComBoxItem", nullptr, mComBoxSRV);
	//Control
	mComBox->SetRect(mComBoxRect);
	mComBox->SetViewPort(GetViewPort());
	mComBox->SetRTWSize(GetRTWSize());
	mComBox->SetContinuous(false);
	mComBox->SetFocusMode(true);
	mComBox->SetMoveMode(false, NoneMove);
	mComBox->SetAnimation(false);
	mComBox->SetControlType(_Button);
	//Static
	mComBox->SetHotKey(0);
	mComBox->SetMKB(GetMKB());
	//Button
	//mComBox->SetText(L"");

	mBtn = new GUIButton("ComBoxItem", nullptr, mBtnSRV);
	//Control
	mBtn->SetRect(mBtnRect);
	mBtn->SetViewPort(GetViewPort());
	mBtn->SetRTWSize(GetRTWSize());
	mBtn->SetContinuous(false);
	mBtn->SetFocusMode(true);
	mBtn->SetMoveMode(false, NoneMove);
	mBtn->SetAnimation(true);
	mBtn->SetControlType(_Button);
	//Static
	mBtn->SetHotKey(0);
	mBtn->SetMKB(GetMKB());
	//Button
	//mBtn->SetText(pText);

}
void GUIComBox::ObjectMove()
{
	if (isMoveMode)
	{
		CalculateRects();
		mComBox->SetRect(mComBoxRect);
		mBtn->SetRect(mBtnRect);
		mListBox->SetRect(mListBoxRect);
		mListBox->SetMoveMode(GetMoveMode(), GetMoveType());
		mListBox->ObjectMove();
	}
	else
	{
		if (mListBox->GetMoveMode())
			mListBox->SetMoveMode(GetMoveMode(), GetMoveType());
	}
}
void GUIComBox::CheckEvented()
{
	if (!isEnable) return;
	GUIStatic::CheckEvented();
	this->ObjectMove();

	mComBox->CheckEvented();
	mBtn->CheckEvented();
	if (isMoveMode) return;


	if (mBtn->GetEvented() ^ mComBox->GetEvented()) // XOR 
	{
		mListBox->CheckEvented();
	}

	if (mListBox->GetIsSelected())
	{
		SetSelectedIdx(mListBox->GetSelectedIdx());
		mBtn->SetEvented(false);
		mComBox->SetEvented(false);
	}
}

void GUIComBox::Render()
{
	if (!isEnable) return;

	RenderTool::SetBlend(AlphaBlend);
	RenderTool::SetViewPort(mRect);

	mComBox->Render();
	mBtn->Render();

	if (mBtn->GetEvented() ^ mComBox->GetEvented()) // XOR 
	{
		mListBox->Render();
	}

	RenderTool::SetBlend(NullState);
}


void GUIComBox::SetItems(std::vector<std::pair<int, std::wstring>> pItems, int pDefaultIdx)
{
	mListBox->SetItems(pItems);
	SetSelectedIdx(pDefaultIdx);
}

void GUIComBox::SetSelectedIdx(int pIdx)
{
	mSelectedIdx = pIdx;
	mComBox->SetText(mListBox->GetItemByIdx(pIdx)->GetText());
	mListBox->SetSelectedIdx(pIdx);
	mListBox->SetIsSelected(false);
}

std::wstring  GUIComBox::GetSelectedIdxName()
{
	return mListBox->GetItemByIdx(mSelectedIdx)->GetText();
}