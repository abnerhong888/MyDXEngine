#ifndef __GUISTATIC_H__
#define __GUISTATIC_H__

#include "..\GraphicCommon.h"
#include "..\Tools\RenderTargetViewTool.h"
#include "..\Tools\TextureTool.h"
#include "..\Tools\RenderTool.h"
#include "..\Tools\DrawTool.h"
#include "..\Tools\Typedefs\ConstantBufferType.h"

#include "..\Font\MyFont.h"

namespace DX11
{
	enum ControlType
	{
		_Button,
		_ComBox,
		_ScrollBar,
		_ListBox,
		_CheckBox,
		_Radio,
		_ControlTotal
	};
	enum ScrollBarType
	{
		_Hor,
		_Ver
	};

	enum MoveType
	{
		MoveX,
		MoveY,
		MoveXY,
		NoneMove
	};

	typedef struct UIRng
	{
		union { struct { float Def, Stp, BigStp, Min, Max; }; float v[5]; };
		UIRng() { ZeroMemory(this, sizeof(UIRng)); }
		UIRng(float _def, float _stp, float _bigstp, float _min, float _max) :
			Def(_def), Stp(_stp), BigStp(_bigstp), Min(_min), Max(_max) {}
		UIRng &operator = (UIRng &in) { memcpy(this, &in, sizeof(UIRng)); return *this; }
	}UIInfo;

	/************************************************************************/
	/*   GUIControl                                                         */
	/************************************************************************/
	class GUIControl
	{
	public:
		virtual void Render() {};
		virtual ~GUIControl() {};
		virtual void CheckEvented() {}

		void			SetName(std::string pName) { mName = pName; }
		std::string		GetName() { return mName; }

		void			SetViewPort(MT::float4 *pViewPort) { mViewport = pViewPort; }
		MT::float4		*GetViewPort() { return mViewport; }

		void			SetRTWSize(MT::float2 *pRTWSize) { mRTWSize = pRTWSize; }
		MT::float2		*GetRTWSize() { return mRTWSize; }

		void			SetRect(MT::float4 pRect) { mRect = pRect; }
		MT::float4		GetRect() { return mRect; }
		MT::float4		*GetRectPtr() { return &mRect; }

		void			SetEnable(bool pEnable) { isEnable = pEnable; }
		bool			GetEnable() { return isEnable; }

		void			SetContinuous(bool pEnable) { isContinuous = pEnable; }
		bool			GetContinuous() { return isContinuous; }

		void			SetAnimation(bool pEnable) { isAnimation = pEnable; }
		bool			GetAnimation() { return isAnimation; }

		void			SetFocusMode(bool pEnable) { isFocusMode = pEnable; }
		bool			GetFocusMode() { return isFocusMode; }

		void			SetMoveMode(bool pEnable, MoveType pType) { isMoveMode = pEnable; mMoveType = pType; }
		bool			GetMoveMode() { return isMoveMode; }

		void			SetControlType(ControlType pType) { mControlType = pType; }
		ControlType		GetControlType() { return mControlType; }

		void			SetMoveModeType(MoveType pType) { mMoveType = pType; }
		MoveType		GetMoveType() { return mMoveType; }

		void			SetRTV(sptrRTVData pRTV) { mRTV = pRTV; }
		sptrRTVData		GetRTV() { return mRTV; }
	protected:
		std::string mName;
		MT::float4 *mViewport = nullptr;
		MT::float2 *mRTWSize = nullptr;
		MT::float4 mRect;
		bool isEnable = true;
		bool isContinuous = false;
		bool isFocusMode = false;
		bool isAnimation = true;
		bool isMoveMode = false;

		MoveType mMoveType = NoneMove;
		ControlType mControlType;
	private:
		sptrRTVData mRTV;
	};

	/************************************************************************/
	/*   GUIStatic                                                          */
	/************************************************************************/
	class GUIStatic : public GUIControl
	{
	public:
		virtual void Render() {};
		virtual ~GUIStatic() {};
		virtual void CheckEvented();

		void			SetMKB(MouseKeyBoard *pMKB) { mMKB = pMKB; }
		MouseKeyBoard	*GetMKB() { return mMKB; }

		void			SetHotKey(unsigned char pHotKey) { mHotKey = pHotKey; }
		unsigned char	GetHotKey() { return mHotKey; }

		void			SetClickDown(bool pEnable) { isMouseDown = pEnable; }
		bool			GetClickDown() { return isMouseDown; }

		void			SetMouseHold(bool pEnable) { isMouseHold = pEnable; }
		bool			GetMouseHold() { return isMouseHold; }

		void			SetMouseOn(bool pEnable) { isMouseOn = pEnable; }
		bool			GetMouseOn() { return isMouseOn; }

		void			SetOnRectOffset(MT::float2 pOffset) { mOnRectOffset = pOffset; }
		MT::float2		GetOnRectOffset() { return mOnRectOffset; }

		bool GetEvented();
		void SetEvented(bool pFlag);
		bool IsWheelUp();
		bool IsWheelDown();
	protected:
		bool isOnRect(MT::float2 pMousePosVp);
		bool isMouseOnRect();
		bool isClickDown();
		bool isClickUp();
		bool isJustClick();
		bool isHotKeyDown();
		bool isHotKeyUp();


		void MoveCalculate();
		MT::float2 GetMousePosVp();

		MouseKeyBoard *mMKB = nullptr;
		unsigned char mHotKey = 0;
		bool isMouseDown = false;
		bool isMouseHold = false;
		bool isMouseEvented = false;
		bool isMouseOn = false;

		bool isKeyDown = false;
		bool isKeyHold = false;
		bool isKeyEvented = false;

		MT::float2 mOnRectOffset;
	private:
		bool MoveflagX = false;
		bool MoveflagY = false;
		float MoveClickposX = 0;
		float MoveClickposY = 0;
	};

}


#endif // __GUISTATIC_H__
