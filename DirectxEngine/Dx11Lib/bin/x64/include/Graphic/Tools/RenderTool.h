#ifndef __RENDERTOOL_H__
#define __RENDERTOOL_H__

#include "DXWIndowTool.h"
#include "SamplerTool.h"
#include "BlendTool.h"
#include "RasterizerTool.h"
#include "DepthStencilTool.h"
#include "ShaderTool.h"
#include "MeshTool.h"
#include "ConstantBufTool.h"
#include "RenderTargetViewTool.h"
#include "TextureTool.h"
#include "DrawTool.h"

#include "Typedefs\MyColor.h"

namespace DX11
{
	

	enum TopologyType
	{
		TriangleList = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		LineList = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		PointList = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	};

	class RenderTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);

		static void SetVertexDataType(TopologyType type);

		static void SetRasterizer(RasterizerType type);
		static void SetRasterizer(sptrRasterizer pRasterizer);

		static void SetSampler(UINT pStartSlot, SamplerType type);
		static void SetSampler(UINT pStartSlot, sptrSampler pSampler);

		static void SetBlend(BlendType type);
		static void SetBlend(sptrBlend pBlend);

		static void SetRenderTargetWindow(WindowType pWindowType, bool pClean = true);
		static void SetRenderTargetWindow(sptrDXWinData pDXWinData, bool pClean = true);
		
		static void SetRenderTargetView(RTVType pRTVType, bool pClean = true, ColorType pColor = Black);
		static void SetRenderTargetView(sptrRTVData pRTVData, bool pClean = true, ColorType pColor = Black);
		
		static void SetRenderTargetViewDepth(RTVType pRTVType, DSViewType pDSViewTpye, bool pCleanRTV = true, bool pCleanDepth = true, ColorType pColor = Black);
		static void SetRenderTargetViewDepth(RTVType pRTVType, sptrDSData pDSData, bool pCleanRTV = true, bool pCleanDepth = true, ColorType pColor = Black);
		static void SetRenderTargetViewDepth(sptrRTVData pRTVData, sptrDSData pDSData, bool pCleanRTV = true, bool pCleanDepth = true, ColorType pColor = Black);
		static void SetRenderTargetViewDepth(sptrRTVData pRTVData, DSViewType pDSViewTpye, bool pCleanRTV = true, bool pCleanDepth = true, ColorType pColor = Black);

		static void SetShaderRV(UINT pStartSlot, ID3D11ShaderResourceView *pSRV);
		static void SetShaderRV(UINT pStartSlot, sptrTexSRV pTexSRV);

		static void SetViewPort(int x, int y, int width, int height);
		static void SetViewPort(float x, float y, float width, float height);
		static void SetViewPort(D3D11_VIEWPORT pViewPort);
		static void SetViewPort(MT::float4 pRect);
		static void SetViewPort(MT::int4 pRect);

		static void SetShader(ShaderTpye type);
		static void SetShader(sptrShaderData pShaderData);

		static void SetMeshDraw(MeshType pMeshtype, DrawType pDrawtype);
		static void SetMesh(MeshType pMeshtype);
		static void MeshDraw(MeshType pMeshtype, DrawType pDrawtype);

		static void SetMeshDraw(sptrMeshData pMeshData, DrawType pDrawtype);
		static void SetMesh(sptrMeshData pMeshData);
		static void MeshDraw(sptrMeshData pMeshData, DrawType pDrawtype);

		static void Flush(WindowType pWindowType);
		static void Flush(sptrDXWinData pDXWinData);

		static void SetContantBuffer(ConstantBufType type);
		template<typename CBstruct>
		static void SetContantBuffer(sptrConstBufData<CBstruct> pConstBufData)
		{
			ConstantBufTool::SetConstantBuf(pConstBufData);
		}

		static void Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV);
		static void Plane(SamplerType pSamplerType, sptrTexSRV pSRV);
		static void Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV, float pColorRatio, float pAlpha);
		static void Plane(SamplerType pSamplerType, sptrTexSRV pSRV, float pColorRatio, float pAlpha);
		static void PlaneColor(SamplerType pSamplerType, ColorType pType, float pAlpha);


		static D3D11_VIEWPORT GetCurrentVP(UINT pViewports);
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext	mDevContext;
	};
}


#endif
