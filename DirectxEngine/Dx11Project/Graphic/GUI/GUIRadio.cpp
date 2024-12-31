#include "GUIRadio.h"
using namespace DX11;

/************************************************************************/
/*   GUIRadio                                                           */
/************************************************************************/

GUIRadio:: ~GUIRadio()
{
	for (std::pair<int, GUICheckBox*> btn : mItems)
	{
		delete btn.second;
	}

	if (mItems.size() > 0) mItems.clear();
	if (mItemRects.size() > 0)mItemRects.clear();
}

GUIRadio::GUIRadio(std::string pName, sptrTexSRV pRadioCheckSRV, sptrTexSRV pRadioUnCheckSRV, ColorType pTextClr)
{
	mName = pName;
	mRadioCheckSRV = pRadioCheckSRV;
	mRadioUnCheckSRV = pRadioUnCheckSRV;

	mTextClr = pTextClr;

}

void GUIRadio::CalculateRects()
{

}

void GUIRadio::Init()
{
	CalculateRects();

}

void GUIRadio::CheckEvented()
{
	if (!isEnable) return;
	for (int i = 0; i < mItems.size(); i++)
	{
		mItems[i]->CheckEvented();
		if (mItems[i]->GetIsCheckChanged())
		{
			if (i != mCheckIdx)
			{
				mItems[i]->SetIsChecked(true);
				mItems[mCheckIdx]->SetIsChecked(false);
				mCheckIdx = i;
			}
			else
			{
				mItems[i]->SetIsChecked(true);
			}
		}
	}
}

void GUIRadio::Render()
{
	if (!isEnable) return;

	for (int i = 0; i < mItems.size(); i++)
	{
		mItems[i]->Render();
	}

}
void GUIRadio::ObjectMove()
{

}

void GUIRadio::SetItems(std::vector<std::tuple<int, std::wstring, MT::float4>> pItems, int pDefaultCheck)
{
	for (std::tuple<int, std::wstring, MT::float4> item : pItems)
	{
		int idx = std::get<int>(item);
		std::wstring str = std::get<std::wstring>(item);

		GUICheckBox *l_checkbox = new GUICheckBox(
			"RadioItem",
			mRadioCheckSRV,
			mRadioUnCheckSRV,
			idx == pDefaultCheck ? true : false,
			mTextClr);

		mItems[idx] = l_checkbox;
		//Control
		l_checkbox->SetRect(mItemRects[idx]);
		l_checkbox->SetViewPort(GetViewPort());
		l_checkbox->SetRTWSize(GetRTWSize());
		l_checkbox->SetContinuous(false);
		l_checkbox->SetFocusMode(false);
		l_checkbox->SetMoveMode(false, NoneMove);
		l_checkbox->SetAnimation(false);
		l_checkbox->SetControlType(_CheckBox);
		l_checkbox->SetRTV(GetRTV());
		//Static
		l_checkbox->SetHotKey(0);
		l_checkbox->SetMKB(GetMKB());
		//CheckBox
		l_checkbox->Init();
		l_checkbox->SetText(str);
	}

	mCheckIdx = pDefaultCheck;
}
void GUIRadio::SetRects(std::vector<std::tuple<int, std::wstring, MT::float4>> pItems)
{
	MT::float4 TotalRect;
	float minX = 9999999.f;
	float maxX = 0.0f;
	float minY = 9999999.f;
	float maxY = 0.0f;
	for (std::tuple<int, std::wstring, MT::float4> item : pItems)
	{
		int idx = std::get<int>(item);
		MT::float4 rect = std::get<MT::float4>(item);
		mItemRects[idx] = rect;

		float L = rect.rx;
		float R = rect.rx + rect.rw;
		float T = rect.ry;
		float B = rect.ry + rect.rh;

		if (L < minX) { minX = L;  TotalRect.rx = L; }
		if (R > maxX) { maxX = R;  TotalRect.rw = R - L; }
		if (T < minY) { minY = T;  TotalRect.ry = T; }
		if (B > maxY) { maxY = B;  TotalRect.rh = B - T; }
	}
	mRect = TotalRect;
}