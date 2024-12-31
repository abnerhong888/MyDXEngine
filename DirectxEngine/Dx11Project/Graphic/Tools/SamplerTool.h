#ifndef __SAMPLERSTATE_H__
#define __SAMPLERSTATE_H__

#include "..\GraphicCommon.h"

namespace DX11
{
	using sptrSampler = std::shared_ptr<ID3D11SamplerState>;

	enum SamplerType
	{
		LinearWarp,
		LinearMirror,
		LinearClamp,
		LinearBorder,
		PointWarp,
		PointMirror,
		PointClamp,
		PointBorder,
		SampTotal,

	};

	class SamplerTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		static ID3D11SamplerState *Get(SamplerType type);
		static void SetSampler(UINT pStartSlot, SamplerType type);
		static void SetSampler(UINT pStartSlot, sptrSampler pSampler);
		static sptrSampler CreateSampler(std::string pName, D3D11_SAMPLER_DESC pDesc);
	protected:
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;

		static sptrSampler mLinearWarp;
		static sptrSampler mLinearMirror;
		static sptrSampler mLinearClamp;
		static sptrSampler mLinearBorder;

		static sptrSampler mPointWarp;
		static sptrSampler mPointMirror;
		static sptrSampler mPointClamp;
		static sptrSampler mPointBorder;
	};

}
#endif // __SAMPLERSTATE_H__