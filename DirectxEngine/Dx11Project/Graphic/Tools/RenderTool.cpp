#include "RenderTool.h"

bool DX11::RenderTool::isInitialized = false;
DX11::sptrDevContext	DX11::RenderTool::mDevContext;
DX11::sptrDevice DX11::RenderTool::mDevice;
bool DX11::RenderTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevice = pDevice;
	mDevContext	= pDevContext;
	isInitialized = true;
	return true;
}

void DX11::RenderTool::SetVertexDataType(TopologyType type)
{
	mDevContext->IASetPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(type));
}

void  DX11::RenderTool::SetRasterizer(RasterizerType type)
{
	RasterizerTool::SetRasterizer(type);
}

void DX11::RenderTool::SetRasterizer(sptrRasterizer pRasterizer)
{
	RasterizerTool::SetRasterizer(pRasterizer);
}

void DX11::RenderTool::SetSampler(UINT pStartSlot, SamplerType type)
{
	SamplerTool::SetSampler(pStartSlot, type);
}

void DX11::RenderTool::SetSampler(UINT pStartSlot, sptrSampler pSampler)
{
	SamplerTool::SetSampler(pStartSlot, pSampler);
}

void DX11::RenderTool::SetBlend(BlendType type)
{
	BlendTool::SetBlend(type);
}

void DX11::RenderTool::SetBlend(sptrBlend pBlend)
{
	BlendTool::SetBlend(pBlend);
}

void DX11::RenderTool::SetRenderTargetWindow(WindowType pWindowType, bool pClean)
{
	DXWIndowTool::SetRenderTargetWindow(pWindowType, pClean);
}

void DX11::RenderTool::SetRenderTargetWindow(sptrDXWinData pDXWinData, bool pClean)
{
	DXWIndowTool::SetRenderTargetWindow(pDXWinData, pClean);
}

void DX11::RenderTool::SetRenderTargetView(RTVType pRTVType, bool pClean, ColorType pColor)
{
	RTVTool::SetRenderTargetView(pRTVType, pClean, pColor);
}

void DX11::RenderTool::SetRenderTargetView(sptrRTVData pRTVData, bool pClean, ColorType pColor)
{
	RTVTool::SetRenderTargetView(pRTVData, pClean, pColor);
}

void DX11::RenderTool::SetRenderTargetViewDepth(RTVType pRTVType, DSViewType pDSViewTpye, bool pCleanRTV, bool pCleanDepth, ColorType pColor)
{
	ID3D11RenderTargetView *l_targetView = RTVTool::Get(pRTVType)->GetRTView();
	ID3D11DepthStencilView *l_depthView = DepthStencilTool::Get(pDSViewTpye);
	mDevContext->OMSetRenderTargets(1, &l_targetView, l_depthView);
	if (pCleanRTV)
	{
		MT::float3 *l_color = Color::Get(pColor);
		float l_cc[4] = { l_color->r, l_color->g, l_color->b, 0.0 };
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}

	if (pCleanDepth)
	mDevContext->ClearDepthStencilView(l_depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11::RenderTool::SetRenderTargetViewDepth(RTVType pRTVType, sptrDSData pDSData, bool pCleanRTV, bool pCleanDepth, ColorType pColor)
{
	ID3D11RenderTargetView *l_targetView = RTVTool::Get(pRTVType)->GetRTView();
	ID3D11DepthStencilView *l_depthView = pDSData->GetDSiew();
	mDevContext->OMSetRenderTargets(1, &l_targetView, l_depthView);
	if (pCleanRTV)
	{
		MT::float3 *l_color = Color::Get(pColor);
		float l_cc[4] = { l_color->r, l_color->g, l_color->b, 0.0 };
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}

	if (pCleanDepth)
		mDevContext->ClearDepthStencilView(l_depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
void DX11::RenderTool::SetRenderTargetViewDepth(sptrRTVData pRTVData, sptrDSData pDSData, bool pCleanRTV, bool pCleanDepth, ColorType pColor)
{
	ID3D11RenderTargetView *l_targetView = pRTVData->GetRTView();
	ID3D11DepthStencilView *l_depthView = pDSData->GetDSiew();
	mDevContext->OMSetRenderTargets(1, &l_targetView, l_depthView);
	if (pCleanRTV)
	{
		MT::float3 *l_color = Color::Get(pColor);
		float l_cc[4] = { l_color->r, l_color->g, l_color->b, 0.0 };
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}
	if (pCleanDepth)
		mDevContext->ClearDepthStencilView(l_depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11::RenderTool::SetRenderTargetViewDepth(sptrRTVData pRTVData, DSViewType pDSViewTpye, bool pCleanRTV, bool pCleanDepth, ColorType pColor)
{
	ID3D11RenderTargetView *l_targetView = pRTVData->GetRTView();
	ID3D11DepthStencilView *l_depthView = DepthStencilTool::Get(pDSViewTpye);
	mDevContext->OMSetRenderTargets(1, &l_targetView, l_depthView);
	if (pCleanRTV)
	{
		MT::float3 *l_color = Color::Get(pColor);
		float l_cc[4] = { l_color->r, l_color->g, l_color->b, 0.0 };
		mDevContext->ClearRenderTargetView(l_targetView, l_cc);
	}
	if (pCleanDepth)
		mDevContext->ClearDepthStencilView(l_depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11::RenderTool::SetShaderRV(UINT pStartSlot, ID3D11ShaderResourceView *pSRV)
{
	mDevContext->PSSetShaderResources(pStartSlot, 1, &pSRV);
}

void DX11::RenderTool::SetShaderRV(UINT pStartSlot, sptrTexSRV pTexSRV)
{
	mDevContext->PSSetShaderResources(pStartSlot, 1, &pTexSRV->SRV);
}

void DX11::RenderTool::SetViewPort(int x, int y, int width, int height)
{
	D3D11_VIEWPORT Viewport;
	Viewport.TopLeftX = static_cast<float>(x);
	Viewport.TopLeftY = static_cast<float>(y);
	Viewport.Width = static_cast<float>(width);
	Viewport.Height = static_cast<float>(height);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	mDevContext->RSSetViewports(1, &Viewport);
}
void DX11::RenderTool::SetViewPort(float x, float y, float width, float height)
{
	D3D11_VIEWPORT Viewport;
	Viewport.TopLeftX = x;
	Viewport.TopLeftY = y;
	Viewport.Width = width;
	Viewport.Height = height;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	mDevContext->RSSetViewports(1, &Viewport);
}
void DX11::RenderTool::SetViewPort(D3D11_VIEWPORT pViewPort)
{
	mDevContext->RSSetViewports(1, &pViewPort);
}

void DX11::RenderTool::SetViewPort(MT::float4 pRect)
{
	D3D11_VIEWPORT Viewport;
	Viewport.TopLeftX = (pRect.rx);
	Viewport.TopLeftY = (pRect.ry);
	Viewport.Width = (pRect.rw);
	Viewport.Height = (pRect.rh);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	mDevContext->RSSetViewports(1, &Viewport);
}
void DX11::RenderTool::SetViewPort(MT::int4 pRect)
{
	D3D11_VIEWPORT Viewport;
	Viewport.TopLeftX = static_cast<float>(pRect.rx);
	Viewport.TopLeftY = static_cast<float>(pRect.ry);
	Viewport.Width = static_cast<float>(pRect.rw);
	Viewport.Height = static_cast<float>(pRect.rh);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	mDevContext->RSSetViewports(1, &Viewport);
}

void DX11::RenderTool::SetContantBuffer(ConstantBufType type)
{
	ConstantBufTool::SetConstantBuf(type);
}

void DX11::RenderTool::SetShader(ShaderTpye type)
{
	ShaderTool::SetShader(type);
}

void DX11::RenderTool::SetShader(sptrShaderData pShaderData)
{
	ShaderTool::SetShader(pShaderData);
}

void DX11::RenderTool::SetMeshDraw(MeshType pMeshtype, DrawType pDrawtype)
{
	MeshTool::SetMeshDraw(pMeshtype, pDrawtype);
}

void DX11::RenderTool::SetMesh(MeshType pMeshtype)
{
	MeshTool::SetMesh(pMeshtype);
}

void DX11::RenderTool::MeshDraw(MeshType pMeshtype, DrawType pDrawtype)
{
	MeshTool::MeshDraw(pMeshtype, pDrawtype);
}

void DX11::RenderTool::SetMeshDraw(sptrMeshData pMeshData, DrawType pDrawtype)
{
	MeshTool::SetMeshDraw(pMeshData, pDrawtype);
}

void DX11::RenderTool::SetMesh(sptrMeshData pMeshData)
{
	MeshTool::SetMesh(pMeshData);
}

void DX11::RenderTool::MeshDraw(sptrMeshData pMeshData, DrawType pDrawtype)
{
	MeshTool::MeshDraw(pMeshData, pDrawtype);
}

void DX11::RenderTool::Flush(WindowType pWindowType)
{
	DXWIndowTool::SetFlush(pWindowType);
}

void DX11::RenderTool::Flush(sptrDXWinData pDXWinData)
{
	DXWIndowTool::SetFlush(pDXWinData);
}


void DX11::RenderTool::Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV)
{
	DrawTool::Plane(pSamplerType, pSRV);
}
void DX11::RenderTool::Plane(SamplerType pSamplerType, sptrTexSRV pSRV)
{
	DrawTool::Plane(pSamplerType, pSRV);
}
void DX11::RenderTool::Plane(SamplerType pSamplerType, ID3D11ShaderResourceView *pSRV, float pColorRatio, float pAlpha)
{
	DrawTool::Plane(pSamplerType, pSRV, pColorRatio, pAlpha);
}
void DX11::RenderTool::Plane(SamplerType pSamplerType, sptrTexSRV pSRV, float pColorRatio, float pAlpha)
{
	DrawTool::Plane(pSamplerType, pSRV, pColorRatio, pAlpha);
}

void DX11::RenderTool::PlaneColor(SamplerType pSamplerType, ColorType pType, float pAlpha)
{
	DrawTool::PlaneColor(pSamplerType, pType, pAlpha);
}

D3D11_VIEWPORT DX11::RenderTool::GetCurrentVP(UINT pViewports)
{
	D3D11_VIEWPORT l_vp;
	mDevContext->RSGetViewports(&pViewports, &l_vp);
	return l_vp;
}