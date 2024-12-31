#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GUIStatic.h"

namespace DX11
{
	/************************************************************************/
	/*   GUICheckbox                                                        */
	/************************************************************************/
	class GUICheckBox : public GUIStatic
	{
	public:
		~GUICheckBox();
		GUICheckBox(std::string pName, sptrTexSRV pCheckSRV, sptrTexSRV pUnCheckSRV, bool pIsChecked, ColorType pTextClr);
		void Render();
		void CheckEvented();
		void Init();
		void SetText(std::wstring pText);
		void ObjectMove();

		std::wstring	GetText() { return mText; }
		void			SetIsChecked(bool pIsChecked) { mIsChecked = pIsChecked; }
		bool			GetIsChecked() { return mIsChecked; }
		bool			GetIsCheckChanged();
	protected:
		void CalculateRects();
	private:
		MT::float4 mCheckBoxRect;
		MT::float2 mTextPos;
		std::wstring mText;
		float mFontSize = 0.0f;
		bool mIsChecked = false;
		bool mIsCheckChanged = false;
		ColorType mTextClr;
		sptrTexSRV mCheckSRV;
		sptrTexSRV mUnCheckSRV;
	};
}



#endif