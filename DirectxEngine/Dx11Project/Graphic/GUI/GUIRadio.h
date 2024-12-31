#ifndef __GUIRADIO_H__
#define __GUIRADIO_H__
#include "GUIStatic.h"
#include "GUICheckBox.h"
namespace DX11
{
	/************************************************************************/
	/*   GUIRadio                                                           */
	/************************************************************************/
	class GUIRadio : public GUIStatic
	{
	public:
		~GUIRadio();
		GUIRadio(std::string pName, sptrTexSRV pRadioCheckSRV, sptrTexSRV pRadioUnCheckSRV, ColorType pTextClr);
		void Render();
		void CheckEvented();
		void Init();
		void ObjectMove();
		void SetItems(std::vector<std::tuple<int, std::wstring, MT::float4>> pItems, int pDefaultCheck);
		void SetRects(std::vector<std::tuple<int, std::wstring, MT::float4>> pItems);
	protected:
		void CalculateRects();
	private:
		ColorType mTextClr;
		sptrTexSRV mRadioCheckSRV;
		sptrTexSRV mRadioUnCheckSRV;
		int mCheckIdx = 0;
		std::unordered_map<int, GUICheckBox*> mItems;
		std::unordered_map<int, MT::float4> mItemRects;
	};
}
#endif // __GUIRADIO_H__
