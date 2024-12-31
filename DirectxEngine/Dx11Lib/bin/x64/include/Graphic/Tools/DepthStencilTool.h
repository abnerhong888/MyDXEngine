#ifndef __DEPTHSTENCIL_H__
#define __DEPTHSTENCIL_H__

#include "..\GraphicCommon.h"

namespace DX11
{
	class DSData;
	using sptrDSData = std::shared_ptr<DSData>;

	enum DSViewType
	{
		DefaultDSView,
		DSViewTotal,

	};

	enum DSStateType
	{
		DefaultDSState,
		DSStateTotal,

	};

	class DepthStencilTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext, int pWidth, int pHeight);
		static ID3D11DepthStencilView *Get(DSViewType type);
		static ID3D11DepthStencilState *Get(DSStateType type);
		static void SetDepthStecilState(DSStateType type);
		static sptrDSData CreateDepthStencilState(
			std::string pName,
			D3D11_TEXTURE2D_DESC pDepthBuffDesc,
			D3D11_DEPTH_STENCIL_DESC pDepthstencildesc);

		static sptrDSData CreateDepthStencilState(std::string pName, int pWidth, int pHeight);

	protected:
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;


		static sptrDSData mDefault;
		
	};


	class DSData
	{
	public:
		DSData(
			ID3D11DepthStencilView		*pDSView,
			ID3D11Texture2D				*pDSBuffer,
			ID3D11DepthStencilState		*pDSState
		);
		ID3D11DepthStencilView		*GetDSiew()const;
		ID3D11Texture2D				*GetDSBuffer()const;
		ID3D11DepthStencilState		*GetDSState()const;
		void Release();
	protected:
	private:
		ID3D11DepthStencilView		*mDepthStencilView = nullptr;
		ID3D11Texture2D				*mDepthStencilBuffer = nullptr;
		ID3D11DepthStencilState		*mDepthStencilState = nullptr;
	};
}


#endif
