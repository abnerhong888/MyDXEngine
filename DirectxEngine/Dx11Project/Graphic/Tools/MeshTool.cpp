#include "MeshTool.h"
#include "Typedefs\VertexType.h"

bool DX11::MeshTool::isInitialized = false;;
DX11::sptrDevice DX11::MeshTool::mDevice;
DX11::sptrDevContext DX11::MeshTool::mDevContext;

DX11::sptrMeshData  DX11::MeshTool::mPlaneMesh;

bool DX11::MeshTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevContext = pDevContext;
	mDevice = pDevice;
	isInitialized = true;

	PlaneVertex PlaneVertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
	};

	DWORD Indices[] =
	{
		0, 1, 3,
		3, 1, 2,
	};
	
	BuffData l_VBufData;
	l_VBufData.Name = "mPlaneMesh";
	l_VBufData.BufCounts = ARRAYSIZE(PlaneVertices);
	l_VBufData.BufStride = sizeof(PlaneVertex);
	l_VBufData.Desc.Usage = D3D11_USAGE_DEFAULT;
	l_VBufData.Desc.ByteWidth = sizeof(PlaneVertex) * ARRAYSIZE(PlaneVertices);
	l_VBufData.Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	l_VBufData.Desc.CPUAccessFlags = 0;
	l_VBufData.Desc.MiscFlags = 0;
	l_VBufData.Initdata.pSysMem = reinterpret_cast<void*>(PlaneVertices);
	
	BuffData l_IBufData;
	l_IBufData.Name = "mPlaneMesh";
	l_IBufData.BufCounts = ARRAYSIZE(Indices);
	l_IBufData.BufStride = sizeof(DWORD);
	l_IBufData.Desc.Usage = D3D11_USAGE_DEFAULT;
	l_IBufData.Desc.ByteWidth = sizeof(DWORD) * ARRAYSIZE(Indices);
	l_IBufData.Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	l_IBufData.Desc.CPUAccessFlags = 0;
	l_IBufData.Desc.MiscFlags = 0;
	l_IBufData.Initdata.pSysMem = reinterpret_cast<void*>(Indices);

	mPlaneMesh = CreateMesh(l_VBufData, l_IBufData);
	if (mPlaneMesh == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	
	return true;
}

void DX11::MeshTool::SetMeshDraw(MeshType pMeshtype, DrawType pDrawtype)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "MeshTool is uninitialized");
		return;
	}
#endif
	SetMesh(pMeshtype);
	MeshDraw(pMeshtype, pDrawtype);

}

void DX11::MeshTool::SetMesh(MeshType pMeshtype)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "MeshTool is uninitialized");
		return;
	}
#endif
	MeshData *l_data = Get(pMeshtype);

	UINT stride = l_data->GetStride();
	UINT offset = 0;

	ID3D11Buffer* l_buffer = l_data->GetVetexBuffer();
	mDevContext->IASetVertexBuffers(0, 1, &l_buffer, &stride, &offset);

	l_buffer = l_data->GetIndexBuffer();
	mDevContext->IASetIndexBuffer(l_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DX11::MeshTool::MeshDraw(MeshType pMeshtype, DrawType pDrawtype)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "MeshTool is uninitialized");
		return;
	}
#endif
	switch (pDrawtype)
	{
	case DX11::DrawIndices:
		mDevContext->DrawIndexed(Get(pMeshtype)->GetIndexCnt(), 0, 0);
		break;
	case DX11::DrawVertexs:
		mDevContext->Draw(Get(pMeshtype)->GetVertexCnt(), 0);
		break;
	}
}

void DX11::MeshTool::SetMeshDraw(sptrMeshData pMeshData, DrawType pDrawtype)
{
	SetMesh(pMeshData);
	MeshDraw(pMeshData, pDrawtype);
}

void DX11::MeshTool::SetMesh(sptrMeshData pMeshData)
{
	UINT stride = pMeshData->GetStride();
	UINT offset = 0;

	ID3D11Buffer* l_buffer = pMeshData->GetVetexBuffer();
	mDevContext->IASetVertexBuffers(0, 1, &l_buffer, &stride, &offset);

	l_buffer = pMeshData->GetIndexBuffer();
	mDevContext->IASetIndexBuffer(l_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DX11::MeshTool::MeshDraw(sptrMeshData pMeshData, DrawType pDrawtype)
{
	switch (pDrawtype)
	{
	case DX11::DrawIndices:
		mDevContext->DrawIndexed(pMeshData->GetIndexCnt(), 0, 0);
		break;
	case DX11::DrawVertexs:
		mDevContext->Draw(pMeshData->GetVertexCnt(), 0);
		break;
	}
}

DX11::MeshData *DX11::MeshTool::Get(MeshType type)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "MeshTool is uninitialized");
		return nullptr;
	}
#endif
	switch (type)
	{
	case DX11::PlaneMesh:
		return mPlaneMesh.get();
	case DX11::MeshTotal:
	default:
		g_SysLog->Log(_ERROR, "Error MeshType %d", static_cast<int>(type));
		return nullptr;
	}
}

DX11::sptrMeshData DX11::MeshTool::CreateMesh(BuffData pVertex, BuffData pIndex)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "MeshTool is uninitialized");
		return nullptr;
	}
#endif
	MeshData *l_MeshData = nullptr;
	
	if (!BufferTool::CreateBuffer(pVertex)) return nullptr;
	if (pIndex.Initdata.pSysMem != nullptr)
	{
		if (!BufferTool::CreateBuffer(pIndex)) return nullptr;
	}
	

	l_MeshData = new MeshData(pVertex, pIndex);
	return SmartPointer::CreateShared(l_MeshData);
}

//////////////////////////////////////////////////////////////////////////
DX11::MeshData::MeshData(BuffData pVdata, BuffData pIdata)
{
	this->mVertexBuffer = pVdata.Buffer;
	this->mVertexStride = pVdata.BufStride;
	this->mVertexCount = pVdata.BufCounts;

	this->mIndexBuffer = pIdata.Buffer;
	this->mIndexCount = pIdata.BufCounts;
}

ID3D11Buffer *DX11::MeshData::GetVetexBuffer()const
{
	return mVertexBuffer;
}

ID3D11Buffer *DX11::MeshData::GetIndexBuffer()const
{
	return mIndexBuffer;
}

int DX11::MeshData::GetIndexCnt()const
{
	return mIndexCount;
}

int DX11::MeshData::GetVertexCnt()const
{
	return mVertexCount;
}

int DX11::MeshData::GetStride()const
{
	return mVertexStride;
}

void DX11::MeshData::Release()
{
	SAFE_RELEASE(mVertexBuffer);
	SAFE_RELEASE(mIndexBuffer);
}