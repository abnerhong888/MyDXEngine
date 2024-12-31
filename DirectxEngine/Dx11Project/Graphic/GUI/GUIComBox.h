#ifndef __GUICOMBOX_H__
#define __GUICOMBOX_H__

#include "GUIStatic.h"
#include "GUIButton.h"
#include "GUIListBox.h"
namespace DX11
{
	/************************************************************************/
	/*   GUIComBox                                                          */
	/************************************************************************/
	class GUIComBox : public GUIStatic
	{
	public:
		~GUIComBox();
		GUIComBox(std::string pName, sptrTexSRV pBtnSRV, sptrTexSRV pComBoxSRV,
			sptrTexSRV pListBoxBackSRV, sptrTexSRV pListBoxScrollBtnSRV,
			sptrTexSRV pListBoxScrollBtnUpSRV, sptrTexSRV pListBoxScrollDownSRV);
		void Render();
		void CheckEvented();
		void Init();
		void SetItems(std::vector<std::pair<int, std::wstring>> pItems, int pDefaultIdx);
		void ObjectMove();

		void			SetSelectedIdx(int pIdx);
		int				GetSelectedIdx() { return mSelectedIdx; }
		std::wstring 	GetSelectedIdxName();

		void			SetListBoxHeight(float pHeight) { mListBoxHeight = pHeight; }
		float			GetListBoxHeight() { return mListBoxHeight; }

	protected:
		void CalculateRects();
	private:
		MT::float4 mComBoxRect;
		MT::float4 mBtnRect;
		MT::float4 mListBoxRect;

		float mListBoxHeight = 0;
		int mSelectedIdx = 0;
		GUIButton *mComBox;
		GUIButton *mBtn;
		GUIListBox *mListBox;
		sptrTexSRV mBtnSRV;
		sptrTexSRV mComBoxSRV;

		sptrTexSRV mLB_BackSRV;
		sptrTexSRV mLB_ScrollBtnSRV, mLB_ScrollBtnUpSRV, mLB_ScrollDownSRV;
	};
}
#endif