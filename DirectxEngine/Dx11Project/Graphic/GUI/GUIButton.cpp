#include "GUIButton.h"
using namespace DX11;
/************************************************************************/
/* GUIButton                                                            */
/************************************************************************/

GUIButton::GUIButton(std::string pName, sptrTexSRV pBtnDown, sptrTexSRV pBtnUp)
{
	mBtnDown = pBtnDown;
	mBtnUp = pBtnUp;
	mName = pName;
}

void GUIButton::SetText(std::wstring pText)
{
	mText = pText;
	mFontSize = mRect.rh - 25.0f;
	mTextPos = MT::float2(mRect.rw / 2, mRect.rh - 12);

	FontInfo l_fontInfo = MyFont::GetIns().GetFontInfo();
	// Get push left text position, same thing in DrawStringPush();
	float l_posX = (mTextPos.x / mRect.rw) * 2.0f - 1.0f;
	for (int i = 0; i < mText.length(); i++)
	{
		wordinfo info = l_fontInfo.WordMap[mText[i]];
		if (info.w == 0 || info.h == 0) { continue; }

		float l_fontRatio = info.w / info.h;
		l_posX -= ((mFontSize / mRect.rw) * l_fontRatio) * 2.0f;
	}

	mTextPos.x = (((l_posX / 2.0f) + 1.0f) / 2.0f) * mRect.rw;
}

void GUIButton::Render()
{
	if (!isEnable) return;
	int o;
	isAnimation ? (isMouseOn ? (isMouseDown ? o = 5 : o = -5) : (isKeyDown ? o = 5 : o = 0)) : o = 0;

	RenderTool::SetViewPort(mRect.rx + o, mRect.ry + o, mRect.rw, mRect.rh);

	RenderTool::SetBlend(AlphaBlend);

	if (mBtnDown)
	{
		if (mBtnUp)
			RenderTool::Plane(LinearWarp, isMouseOn ? (isMouseDown ? mBtnDown : mBtnUp) : (isKeyDown ? mBtnDown : mBtnUp),
				isMouseOn ? (isMouseDown ? 1.0f : 5.0f) : 1.0f, -1.0f);
		else
			RenderTool::PlaneColor(LinearWarp, isMouseOn ? (isMouseDown ? MineralBlue : BabyBlue) : isKeyDown ? MineralBlue : DodgerBlue, 1.0);
	}
	else
	{
		if (mBtnUp)
			RenderTool::Plane(LinearWarp, mBtnUp, isMouseOn ? (isMouseDown ? 0.5f : 5.0f) : (isKeyDown ? 0.5f : 1.0f), -1.0f);
		else
			RenderTool::PlaneColor(LinearWarp, isMouseOn ? (isMouseDown ? MineralBlue : BabyBlue) : isKeyDown ? MineralBlue : DodgerBlue, 1.0);
	}

	RenderTool::SetBlend(NullState);
	if (!mText.empty())
		MyFont::GetIns().DrawString((int)mTextPos.x, (int)mTextPos.y, mFontSize, isMouseOn ? (isMouseDown ? White : Gray) : White, mText.c_str());
}