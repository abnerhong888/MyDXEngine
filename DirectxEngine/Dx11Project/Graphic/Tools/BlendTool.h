#ifndef __BLENDSTATE_H__
#define __BLENDSTATE_H__

#include "..\GraphicCommon.h"

namespace DX11
{
	using sptrBlend = std::shared_ptr<ID3D11BlendState>;

	enum BlendType
	{
		AlphaBlend,
		AddBlend,
		FontBlend,
		DstZeroBlend,
		NullState,
		BlendTotal,
	};
	class BlendTool
	{
	public:
		
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		static ID3D11BlendState *Get(BlendType type);
		static void SetBlend(BlendType type);
		static void SetBlend(sptrBlend pBlend);
		static sptrBlend CreateBlend(std::string pName, D3D11_BLEND_DESC pDesc);
	protected:

	private:
		static sptrDevContext mDevContext;
		static sptrDevice mDevice;
		static bool isInitialized;
		static sptrBlend mAlphaBlend;
		static sptrBlend mAddBlend;
		static sptrBlend mFontBlend;
		static sptrBlend mDstZeroBlend;
	};

}

#endif
