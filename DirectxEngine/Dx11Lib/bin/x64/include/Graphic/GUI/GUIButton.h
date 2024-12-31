#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GUIStatic.h"

namespace DX11
{
	/************************************************************************/
	/*   GUIButton                                                          */
	/************************************************************************/
	class GUIButton : public GUIStatic
	{
	public:
		~GUIButton() {};
		GUIButton(std::string pName, sptrTexSRV pBtnDown, sptrTexSRV pBtnUp);
		void Render();
		void SetText(std::wstring pText);
		std::wstring	GetText() { return mText; }
	protected:
	private:
		sptrTexSRV mBtnDown;
		sptrTexSRV mBtnUp;
		std::wstring mText;
		MT::float2 mTextPos;
		float mFontSize = 0.0f;

	};
}

#endif // __GUIBUTTON_H__
