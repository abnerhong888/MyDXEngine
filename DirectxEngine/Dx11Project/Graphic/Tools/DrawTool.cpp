#include "DrawTool.h"

void DX11::DrawTool::Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV)
{
	RenderTool::SetVertexDataType(TriangleList);
	RenderTool::SetSampler(0, pSamplerType);
	RenderTool::SetRasterizer(Solid_None);
	RenderTool::SetShaderRV(0, pSRV);
	RenderTool::SetShader(Tex2D);
	RenderTool::SetMeshDraw(PlaneMesh, DrawIndices);
}

void DX11::DrawTool::Plane(SamplerType pSamplerType, sptrTexSRV pSRV)
{
	Plane(pSamplerType, pSRV->SRV);
}

void DX11::DrawTool::Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV, float pColorRatio, float pAlpha)
{
	RenderTool::SetVertexDataType(TriangleList);
	RenderTool::SetSampler(0, pSamplerType);
	RenderTool::SetRasterizer(Solid_None);
	RenderTool::SetShaderRV(0, pSRV);
	RenderTool::SetShader(Tex2D_ColorRatioAlpha);

	Tex2D_ColorRatioAlphaCB *l_data = (Tex2D_ColorRatioAlphaCB *)ConstantBufTool::GetCBData(Tex2D_ColorRatioAlpha_CB);
	l_data->Alpha = pAlpha;
	l_data->ColorRatio = pColorRatio;
	ConstantBufTool::SetConstantBuf(Tex2D_ColorRatioAlpha_CB);
	RenderTool::SetMeshDraw(PlaneMesh, DrawIndices);
}

void DX11::DrawTool::Plane(SamplerType pSamplerType, sptrTexSRV pSRV, float pColorRatio, float pAlpha)
{
	Plane(pSamplerType, pSRV->SRV, pColorRatio, pAlpha);
}

void DX11::DrawTool::PlaneColor(SamplerType pSamplerType, ColorType pType, float pAlpha)
{
	RenderTool::SetVertexDataType(TriangleList);
	RenderTool::SetSampler(0, pSamplerType);
	RenderTool::SetRasterizer(Solid_None);
	RenderTool::SetShader(Tex2D_ColorAlpha);

	Tex2D_ColorAlphaCB *l_data = (Tex2D_ColorAlphaCB *)ConstantBufTool::GetCBData(Tex2D_ColorAlpha_CB);
	MT::float3 *clr = Color::Get(pType);
	l_data->r = clr->r;
	l_data->g = clr->g;
	l_data->b = clr->b;
	l_data->Alpha = pAlpha;
	ConstantBufTool::SetConstantBuf(Tex2D_ColorAlpha_CB);
	RenderTool::SetMeshDraw(PlaneMesh, DrawIndices);

}
