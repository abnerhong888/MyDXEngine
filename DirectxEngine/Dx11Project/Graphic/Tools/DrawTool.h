#ifndef __DRAWTOOL_H__
#define __DRAWTOOL_H__

#include "..\GraphicCommon.h"
#include "RenderTool.h"
#include "Typedefs\MyColor.h"
namespace DX11
{
	class DrawTool
	{
	public:
		static void Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV);
		static void Plane(SamplerType pSamplerType, sptrTexSRV pSRV);
		static void Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV, float pColorRatio, float pAlpha);
		static void Plane(SamplerType pSamplerType, sptrTexSRV pSRV, float pColorRatio, float pAlpha);

		static void PlaneColor(SamplerType pSamplerType, ColorType pType, float pAlpha);
		
	};
}


#endif

