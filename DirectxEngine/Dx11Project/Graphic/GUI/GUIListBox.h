#ifndef __GUILISTBOX_H__
#define __GUILISTBOX_H__
#include "GUIStatic.h"
#include "GUIButton.h"
#include "GUIScrollBar.h"

namespace DX11
{
	/************************************************************************/
	/*   GUIListBox                                                         */
	/************************************************************************/
	class GUIListBox : public GUIStatic
	{
	public:
		~GUIListBox();
		GUIListBox(std::string pName, sptrTexSRV pBackSRV, sptrTexSRV pScrollBtnSRV, sptrTexSRV pScrollBtnUpSRV, sptrTexSRV pScrollDownSRV);
		void Init();
		void Render();
		void CheckEvented();
		void SetItems(std::vector<std::pair<int, std::wstring>> pItems);
		void ObjectMove();

		void		SetSelectedIdx(int pIdx) { mSelectedIdx = pIdx; }
		int			GetSelectedIdx() { return mSelectedIdx; }

		void		SetIsSelected(bool pIsSelcected) { mIsSelected = pIsSelcected; }
		bool		GetIsSelected();

		void		SetItemHeight(float pHeight) { mItemHeight = pHeight; }
		float		GetItemHeight() { return mItemHeight; }
		GUIButton*	GetItemByIdx(int pIdx) { return mItems[pIdx]; }


	protected:
		void CalculateRects();
	private:
		MT::float4 mScrollBarRect;
		float mItemHeight = 50.0f;
		std::unordered_map<int, GUIButton*> mItems;
		GUIScrollBar *mScrollBar;
		sptrTexSRV mBackSRV;
		sptrTexSRV mScrollBtnSRV, mScrollBtnUpSRV, mScrollDownSRV;

		sptrRTVData mBackRTV;
		MT::float4 mBackRect;

		int mSelectedIdx = 0;
		bool mIsSelected = false;
	};
}


#endif
