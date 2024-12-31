#ifndef __RASTERIZESTATE_H__
#define __RASTERIZESTATE_H__

#include "..\GraphicCommon.h"

namespace DX11
{
	using sptrRasterizer = std::shared_ptr<ID3D11RasterizerState>;

	enum RasterizerType
	{
		Solid_Back,
		Solid_None,
		Wire_Back,
		Wire_None,
		RasterizerTotal,
	};

	class RasterizerTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		static ID3D11RasterizerState *Get(RasterizerType type);
		static void SetRasterizer(RasterizerType type);
		static void SetRasterizer(sptrRasterizer pRasterizer);
		static sptrRasterizer CreateRasterizer(std::string pName, D3D11_RASTERIZER_DESC pDesc);
	protected:
	private:
		static bool isInitialized;
		static sptrDevContext mDevContext;
		static sptrDevice mDevice;
		static sptrRasterizer mSolid_Back;
		static sptrRasterizer mSolid_None;
		static sptrRasterizer mWire_Back;
		static sptrRasterizer mWire_None;
	};



}// namespace DX11
#endif