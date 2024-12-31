#ifndef __RENDERTARGETVIEW_H__
#define __RENDERTARGETVIEW_H__

#include "..\GraphicCommon.h"
#include "TextureTool.h"
#include "Typedefs\MyColor.h"
namespace DX11
{
	class RTVData;
	using sptrRTVData = std::shared_ptr<RTVData>;

	enum RTVType
	{
		OutView,

		RTVTotal,
	};

	class RTVTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext, int pDisplayTexW, int pDisplayTexH);
		static RTVData *Get(RTVType type);
		static sptrRTVData GetSptr(RTVType type);
		static void SetRenderTargetView(RTVType pRTVType, bool pClean = true, ColorType pColor = Black);
		static void SetRenderTargetView(sptrRTVData pRTVData, bool pClean = true, ColorType pColor = Black);

		static sptrRTVData CreateRTV(std::string pName, int pTexW, int pTexH, TextureType pTexType, TextureFormat pTexFormat);
		
	protected:

	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;
		static sptrRTVData mOutView;
	};


	class RTVData
	{
	public:
		RTVData(
			ID3D11RenderTargetView		*pRTView,
			ID3D11ShaderResourceView	*pSRV,
			ID3D11Resource				*pTex
		);
		ID3D11RenderTargetView		*GetRTView()const;
		ID3D11ShaderResourceView	*GetSRV()const;
		ID3D11Resource				*GetTex()const;
		void Release();
	protected:
	private:
		ID3D11RenderTargetView		*mRenderTargetView = nullptr;
		ID3D11ShaderResourceView	*mShaderResourceView = nullptr;
		ID3D11Resource				*mTexture = nullptr;
	};
}


#endif