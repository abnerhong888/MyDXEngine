#include "MYGUI.h"
using namespace DX11;
/************************************************************************/
/* MYGUI                                                                */
/************************************************************************/

MYGUI::~MYGUI()
{
	if (mControls.size() > 0)
	{
		for (std::pair<std::string, GUIControl*> ctl : mControls)
		{
			delete ctl.second;
		}
		mControls.clear();
	}
}

bool MYGUI::Initialize(std::string pName, sptrDevice pDevice, sptrDevContext pDevContext, MT::int4 pViewport, MT::int2 pRTWSize)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }
	mDevice = pDevice;
	mDevContext = pDevContext;
	mName = pName;

	mViewport = MT::float4((float)pViewport.rx, (float)pViewport.ry, (float)pViewport.rw, (float)pViewport.rh);
	mRTWSize = MT::float2((float)pRTWSize.x, (float)pRTWSize.y);

	mControls.clear();

	MyFont::GetIns().Initialize(D_FONT_FILE, mDevice, mDevContext);
	mRTV = RTVTool::CreateRTV(mName, (int)mViewport.rw, (int)mViewport.rh, RENDER_SRV_TARGET, RGBA8_U);
	if (mRTV == nullptr) return false;

	mBtnUp				= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("btn.png"));
	mComBoxBtn			= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("ComBoxbtn.png"));

	mScrollBarBtnU		= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("ScrollBarUp.png"));
	mScrollBarBtnD		= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("ScrollBarDown.png"));
	mScrollBarBtnR		= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("ScrollBarRight.png"));
	mScrollBarBtnL		= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("ScrollBarLeft.png"));

	mCheckSRV			= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("Check.jpg"));
	mUnCheckSRV			= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("Uncheck.jpg"));

	mRadioCheckSRV		= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("Radio_check.png"));
	mRadioUnCheckSRV	= TextureTool::CreateSRVFromFile_2D(D_GUIFOLDER("Radio_uncheck.png"));
	

	return true;
}

void MYGUI::ParseMouseKeyboard(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MouseKeyBoard::ParseEvent(&mMKB, hWnd, message, wParam, lParam);
	
	for (std::pair<std::string, GUIControl*> ctl : mControls)
	{
		ctl.second->CheckEvented();
	}

	// Release ALL queue Buffer if no use
	KeyboardClass *keyboard = mMKB.GetKeyboard();
	MouseClass *mouse = mMKB.GetMouse();
	while (!keyboard->CharBufferIsEmpty()) { unsigned char ch = keyboard->ReadChar(); }
	while (!keyboard->KeyBufferIsEmpty()) { KeyboardEvent kbe = keyboard->ReadKey(); }
	while (!mouse->EventBufferIsEmpty()) { MouseEvent me = mouse->ReadEvent(); }
}

ID3D11ShaderResourceView *MYGUI::GetSRV()
{
	return mRTV->GetSRV();
}

void MYGUI::Render()
{
	RenderTool::SetVertexDataType(TriangleList);
	RenderTool::SetRenderTargetView(mRTV, true);

	for (std::pair<std::string, GUIControl*> ctl : mControls)
	{
		//RenderTool::SetRenderTargetView(mRTV, false);
		ctl.second->Render();
	}
}

bool MYGUI::CheckSameItemName(std::string pName, std::string pControlName)
{
	for (std::pair<std::string, GUIControl*> ctl : mControls)
	{
		if (ctl.first == pName)
		{
			g_SysLog->Log(_WARNING, "GUI -> %s add same control name: %s", pControlName.c_str(), pName.c_str());
			return true;
		}
	}
	return false;
}

void MYGUI::AddBtn(std::string pName, MT::float4 pRect, std::wstring pText,
	unsigned char pHotKey, bool pIsContinuous, bool pIsAnimation,
	sptrTexSRV pBtnDown, sptrTexSRV pBtnUp)
{
	if (CheckSameItemName(pName, "Button")) return;

	GUIButton *l_Btn = new GUIButton(pName, pBtnDown ? pBtnDown : nullptr, pBtnUp ? pBtnUp : mBtnUp);
	mControls[pName] = l_Btn;

	//Control
	l_Btn->SetRect(pRect);
	l_Btn->SetViewPort(&mViewport);
	l_Btn->SetRTWSize(&mRTWSize);
	l_Btn->SetContinuous(pIsContinuous);
	l_Btn->SetFocusMode(false);
	l_Btn->SetMoveMode(false, NoneMove);
	l_Btn->SetAnimation(pIsAnimation);
	l_Btn->SetControlType(_Button);
	l_Btn->SetRTV(mRTV);
	//Static
	l_Btn->SetHotKey(pHotKey);
	l_Btn->SetMKB(&mMKB);
	//Button
	l_Btn->SetText(pText);
}

void MYGUI::AddScrollBar(std::string pName, MT::float4 pRect, ScrollBarType pType, UIRng pRng,
	sptrTexSRV pBtnSRV, sptrTexSRV pBarSRV,
	sptrTexSRV pBtnUSRV, sptrTexSRV pBtnDSRV,
	sptrTexSRV pBtnRSRV, sptrTexSRV pBtnLSRV)
{
	if (CheckSameItemName(pName, "ScrollBar")) return;
	
	GUIScrollBar *l_scrollbar = nullptr;
	if (pType == _Hor)
	{
		l_scrollbar = new GUIScrollBar(pName, pType,
			pBtnSRV ? pBtnSRV : /*nullptr*/mBtnUp, pBarSRV ? pBarSRV : nullptr,
			nullptr, nullptr,
			pBtnRSRV ? pBtnRSRV : mScrollBarBtnR, pBtnLSRV ? pBtnLSRV : mScrollBarBtnL
		);
	}
	else if (pType == _Ver)
	{
		l_scrollbar = new GUIScrollBar(pName, pType,
			pBtnSRV ? pBtnSRV : /*nullptr*/mBtnUp, pBarSRV ? pBarSRV : nullptr,
			pBtnUSRV ? pBtnUSRV : mScrollBarBtnU, pBtnDSRV ? pBtnDSRV : mScrollBarBtnD,
			nullptr, nullptr
		);
	}
	mControls[pName] = l_scrollbar;

	//Control
	l_scrollbar->SetRect(pRect);
	l_scrollbar->SetViewPort(&mViewport);
	l_scrollbar->SetRTWSize(&mRTWSize);
	l_scrollbar->SetContinuous(false);
	l_scrollbar->SetFocusMode(false);
	l_scrollbar->SetMoveMode(false, NoneMove);
	l_scrollbar->SetAnimation(false);
	l_scrollbar->SetControlType(_ScrollBar);
	l_scrollbar->SetRTV(mRTV);
	//Static
	l_scrollbar->SetHotKey(0);
	l_scrollbar->SetMKB(&mMKB);
	//ScrollBar
	l_scrollbar->Init();
	l_scrollbar->SetRng(pRng);

}

void MYGUI::AddListBox(std::string pName, MT::float4 pRect, std::vector<std::pair<int, std::wstring>> pItems, sptrTexSRV pBackSRV)
{
	if (CheckSameItemName(pName, "List")) return;

	GUIListBox *l_listbox = nullptr;

	l_listbox = new GUIListBox(pName, pBackSRV ? pBackSRV: nullptr, mBtnUp, mScrollBarBtnU, mScrollBarBtnD);
	mControls[pName] = l_listbox;

	//Control
	l_listbox->SetRect(pRect);
	l_listbox->SetViewPort(&mViewport);
	l_listbox->SetRTWSize(&mRTWSize);
	l_listbox->SetContinuous(false);
	l_listbox->SetFocusMode(false);
	l_listbox->SetMoveMode(false, NoneMove);
	l_listbox->SetAnimation(false);
	l_listbox->SetControlType(_ListBox);
	l_listbox->SetRTV(mRTV);
	//Static
	l_listbox->SetHotKey(0);
	l_listbox->SetMKB(&mMKB);
	//ListBox
	l_listbox->Init();
	l_listbox->SetItems(pItems);
}

void MYGUI::AddComBox(std::string pName, MT::float4 pRect, 
	float pListBoxH, std::vector<std::pair<int, std::wstring>> pItems, 
	int pDefaultIdx, sptrTexSRV pBtnSRV, sptrTexSRV pComBoxSRV)
{
	if (CheckSameItemName(pName, "ComBox")) return;

	GUIComBox *l_combox = new GUIComBox(
		pName,
		pBtnSRV ? pBtnSRV : mComBoxBtn,
		pComBoxSRV ? pComBoxSRV : nullptr,
		nullptr,
		mBtnUp,
		mScrollBarBtnU,
		mScrollBarBtnD);

	mControls[pName] = l_combox;

	//Control
	l_combox->SetRect(pRect);
	l_combox->SetViewPort(&mViewport);
	l_combox->SetRTWSize(&mRTWSize);
	l_combox->SetContinuous(false);
	l_combox->SetFocusMode(true);
	l_combox->SetMoveMode(false, NoneMove);
	l_combox->SetAnimation(true);
	l_combox->SetControlType(_ComBox);
	l_combox->SetRTV(mRTV);
	//Static
	l_combox->SetHotKey(0);
	l_combox->SetMKB(&mMKB);
	//ComBox
	l_combox->SetListBoxHeight(pListBoxH);
	l_combox->Init();
	l_combox->SetItems(pItems, pDefaultIdx);
}

void MYGUI::AddCheckBox(std::string pName, MT::float4 pRect, std::wstring pText, ColorType pTextClr,
	bool pIsChecked, sptrTexSRV pCheckSRV, sptrTexSRV pUnCheckSRV)
{
	if (CheckSameItemName(pName, "CheckBox")) return;

	GUICheckBox *l_checkbox = new GUICheckBox(
		pName, 
		pCheckSRV ? pCheckSRV : mCheckSRV, 
		pUnCheckSRV ? pUnCheckSRV : mUnCheckSRV,
		pIsChecked,
		pTextClr);

	mControls[pName] = l_checkbox;

	//Control
	l_checkbox->SetRect(pRect);
	l_checkbox->SetViewPort(&mViewport);
	l_checkbox->SetRTWSize(&mRTWSize);
	l_checkbox->SetContinuous(false);
	l_checkbox->SetFocusMode(false);
	l_checkbox->SetMoveMode(false, NoneMove);
	l_checkbox->SetAnimation(false);
	l_checkbox->SetControlType(_CheckBox);
	l_checkbox->SetRTV(mRTV);
	//Static
	l_checkbox->SetHotKey(0);
	l_checkbox->SetMKB(&mMKB);
	//CheckBox
	l_checkbox->Init();
	l_checkbox->SetText(pText);
}


void MYGUI::AddRadios(std::string pName, std::vector<std::tuple<int, std::wstring, MT::float4>> pItems,
	int pDefaultCheck, ColorType pTextClr, sptrTexSRV pRadioCheckSRV, sptrTexSRV pRadioUnCheckSRV)
{
	if (CheckSameItemName(pName, "Radio")) return;

	GUIRadio *l_radio = new GUIRadio(pName,
		pRadioCheckSRV ? pRadioCheckSRV : mRadioCheckSRV,
		pRadioUnCheckSRV ? pRadioUnCheckSRV : mRadioUnCheckSRV,
		pTextClr);

	mControls[pName] = l_radio;

	//Control
	l_radio->SetRect(MT::float4());
	l_radio->SetViewPort(&mViewport);
	l_radio->SetRTWSize(&mRTWSize);
	l_radio->SetContinuous(false);
	l_radio->SetFocusMode(false);
	l_radio->SetMoveMode(false, NoneMove);
	l_radio->SetAnimation(false);
	l_radio->SetControlType(_Radio);
	l_radio->SetRTV(mRTV);
	//Static
	l_radio->SetHotKey(0);
	l_radio->SetMKB(&mMKB);
	//CheckBox
	l_radio->SetRects(pItems);
	l_radio->Init();
	l_radio->SetItems(pItems, pDefaultCheck >= pItems.size() ? 0 : pDefaultCheck);
}