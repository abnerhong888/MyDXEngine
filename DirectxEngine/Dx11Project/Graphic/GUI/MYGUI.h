#ifndef __MYGUI_H__
#define __MYGUI_H__

#include "GUIStatic.h"
#include "GUIButton.h"
#include "GUICheckBox.h"
#include "GUIComBox.h"
#include "GUIListBox.h"
#include "GUIRadio.h"
#include "GUIScrollBar.h"

#define D_GUIFOLDER(_f) L".\\img\\GUI\\" ## _f

namespace DX11
{	
	/************************************************************************/
	/*   MYGUI                                                              */
	/************************************************************************/
	class MYGUI
	{
	public:
		~MYGUI();
		bool Initialize(std::string pName, sptrDevice pDevice, sptrDevContext pDevContext, MT::int4 pViewport, MT::int2 pRTWSize);
		void ParseMouseKeyboard(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		ID3D11ShaderResourceView *GetSRV();

		void Render();

		void AddBtn(std::string pName, MT::float4 pRect, std::wstring pText,
			unsigned char pHotKey = 0, bool pIsContinuous = false,bool pIsAnimation = true, 
			sptrTexSRV pBtnDown = nullptr, sptrTexSRV pBtnUp = nullptr);

		void AddScrollBar(std::string pName, MT::float4 pRect, ScrollBarType pType, UIRng pRng,
			sptrTexSRV pBtnSRV = nullptr, sptrTexSRV pBarSRV = nullptr,
			sptrTexSRV pBtnUSRV = nullptr, sptrTexSRV pBtnDSRV = nullptr,
			sptrTexSRV pBtnRSRV = nullptr, sptrTexSRV pBtnLSRV = nullptr);

		void AddListBox(std::string pName, MT::float4 pRect, std::vector<std::pair<int, std::wstring>> pItems, sptrTexSRV pBackSRV = nullptr);

		void AddComBox(std::string pName, MT::float4 pRect, float pListBoxH, std::vector<std::pair<int, std::wstring>> pItems, 
			int pDefaultIdx = 0, sptrTexSRV pBtnSRV = nullptr, sptrTexSRV pComBoxSRV = nullptr);

		void AddCheckBox(std::string pName, MT::float4 pRect, std::wstring pText, ColorType pTextClr = Black,
			bool pIsChecked = false, sptrTexSRV pCheckSRV = nullptr, sptrTexSRV pUnCheckSRV = nullptr);

		void AddRadios(std::string pName, std::vector<std::tuple<int, std::wstring, MT::float4>> pItems, 
			int pDefaultCheck = 0, ColorType pTextClr = Black, 
			sptrTexSRV pRadioCheckSRV = nullptr, sptrTexSRV pRadioUnCheckSRV = nullptr);


		template<typename T>
		T *GetOBJ(std::string pName)
		{
			for (std::pair<std::string, GUIControl*> ctl : mControls)
			{
				if (ctl.second->GetControlType() == GetControlTypeByClass<T>())
				{
					if (ctl.first == pName)
					{
						return (T*)ctl.second;
					}
				}

			}
			return nullptr;
		}


		void SetRTWSize(MT::float2 pSize)				{ mRTWSize = pSize; }
	protected:
		bool CheckSameItemName(std::string pName, std::string pControlName);
		template<typename T>
		ControlType GetControlTypeByClass()
		{
			if (std::is_same<GUIButton, T>::value)		return ControlType::_Button;
			if (std::is_same<GUIScrollBar, T>::value)	return ControlType::_ScrollBar;
			if (std::is_same<GUIComBox, T>::value)		return ControlType::_ComBox;
			if (std::is_same<GUIListBox, T>::value)		return ControlType::_ListBox;
			if (std::is_same<GUICheckBox, T>::value)	return ControlType::_CheckBox;
			if (std::is_same<GUIRadio, T>::value)		return ControlType::_Radio;
		}
	private:
		
		bool isInitialized = false;
		std::string mName;
		sptrDevice mDevice;
		sptrDevContext mDevContext;
		sptrRTVData mRTV;
		MT::float4 mViewport;
		MT::float2 mRTWSize;
		MouseKeyBoard mMKB;

		std::unordered_map<std::string, GUIControl*> mControls;

		sptrTexSRV mBtnUp;
		sptrTexSRV mComBoxBtn;
		sptrTexSRV mScrollBarBtnU;
		sptrTexSRV mScrollBarBtnD;
		sptrTexSRV mScrollBarBtnR;
		sptrTexSRV mScrollBarBtnL;

		sptrTexSRV mCheckSRV;
		sptrTexSRV mUnCheckSRV;

		sptrTexSRV mRadioCheckSRV;
		sptrTexSRV mRadioUnCheckSRV;

	};
}


#endif

