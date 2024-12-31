#include "GUICheckBox.h"
using namespace DX11;

/************************************************************************/
/*   GUICheckbox                                                        */
/************************************************************************/

GUICheckBox::~GUICheckBox()
{

}

GUICheckBox::GUICheckBox(std::string pName, sptrTexSRV pCheckSRV, sptrTexSRV pUnCheckSRV,
	bool pIsChecked, ColorType pTextClr)
{
	mName = pName;
	mCheckSRV = pCheckSRV;
	mUnCheckSRV = pUnCheckSRV;
	mIsChecked = pIsChecked;
	mTextClr = pTextClr;
}

void GUICheckBox::CalculateRects()
{
	mCheckBoxRect = MT::float4(mRect.rx, mRect.ry, mRect.rh, mRect.rh);
	mTextPos = MT::float2(mCheckBoxRect.rw + 15.f, mRect.rh + 2.f);
	mFontSize = mRect.rh;
}

void GUICheckBox::Init()
{
	CalculateRects();
}

void GUICheckBox::CheckEvented()
{
	if (!isEnable) return;
	GUIStatic::CheckEvented();

	this->ObjectMove();
	if (isMoveMode) return;

	if (GUIStatic::GetEvented())
	{
		mIsChecked = !mIsChecked;
		mIsCheckChanged = true;
	}


}

void GUICheckBox::Render()
{
	if (!isEnable) return;

	RenderTool::SetBlend(AlphaBlend);
	RenderTool::SetViewPort(mCheckBoxRect);

	if (mCheckSRV == nullptr && mUnCheckSRV == nullptr)
	{
		if (mIsChecked)
			RenderTool::PlaneColor(LinearWarp, Red, 1.0f);
		else
			RenderTool::PlaneColor(LinearWarp, White, 1.0f);
	}
	else
	{
		if (mIsChecked)
			if (mCheckSRV)
				RenderTool::Plane(LinearWarp, mCheckSRV, 1.0f, -1.0f);
			else
				RenderTool::PlaneColor(LinearWarp, Red, 1.0f);
		else
			if (mUnCheckSRV)
				RenderTool::Plane(LinearWarp, mUnCheckSRV, 1.0f, -1.0f);
			else
				RenderTool::PlaneColor(LinearWarp, White, 1.0f);
	}

	RenderTool::SetBlend(DstZeroBlend);
	if (isMouseOn) { RenderTool::PlaneColor(LinearWarp, BabyBlue, 0.5f); }


	RenderTool::SetBlend(NullState);

	RenderTool::SetViewPort(mRect);
	if (!mText.empty())
		MyFont::GetIns().DrawString((int)mTextPos.x, (int)mTextPos.y, mFontSize, mTextClr, mText.c_str());

}

void GUICheckBox::ObjectMove()
{
	if (isMoveMode)
	{
		CalculateRects();
	}
}

void GUICheckBox::SetText(std::wstring pText)
{
	mText = pText;
}

bool GUICheckBox::GetIsCheckChanged()
{
	if (mIsCheckChanged)
	{
		mIsCheckChanged = false;
		return true;
	}
	return false;
}