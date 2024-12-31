#ifndef __GUISCROLLBAR_H__
#define __GUISCROLLBAR_H__

#include "GUIStatic.h"
#include "GUIButton.h"

namespace DX11
{
	/************************************************************************/
	/*   GUIScrollBar                                                       */
	/************************************************************************/
	class GUIScrollBar : public GUIStatic
	{
	public:
		~GUIScrollBar();
		GUIScrollBar(std::string pName, ScrollBarType pType,
			sptrTexSRV pBtnSRV, sptrTexSRV pBarSRV,
			sptrTexSRV pBtnUSRV, sptrTexSRV pBtnDSRV,
			sptrTexSRV pBtnRSRV, sptrTexSRV pBtnLSRV);
		void Init();
		void Render();

		void CheckEvented();
		void SetRng(UIRng pRng);
		void SetIncrease();
		void SetDecrease();
		UIRng GetRng();
		void ObjectMove();
		float GetCurrentVal();
		float GetDiffVal();
		float GetIsValChagne();
	protected:
		void CheckBtnValueState();
		void CalculateRects();
	private:
		MT::float4 mBarRect, mBtnRect, mBtnURect, mBtnDRect, mBtnRRect, mBtnLRect;
		GUIButton *mBar, *mBtn, *mBtnU, *mBtnD, *mBtnR, *mBtnL;
		sptrTexSRV mBtnSRV, mBarSRV, mBtnUSRV, mBtnDSRV, mBtnRSRV, mBtnLSRV;
		ScrollBarType mScrollType;
		UIRng mBtnRng;
		UIRng mRng;
		float mBtnUnit = 0.0f;
		float mCurrentVal = 0.0f;
		float mDiffVal = 0.0f;
		float mPreVal = 0.0f;
		bool mIsValChange = false;
	};
}

#endif // __GUISCROLLBAR_H__
