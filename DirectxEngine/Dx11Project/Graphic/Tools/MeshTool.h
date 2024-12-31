#ifndef __MESH_H__
#define __MESH_H__

#include "..\GraphicCommon.h"
#include "BufferTool.h"

namespace DX11
{
	class MeshData;
	using sptrMeshData = std::shared_ptr<MeshData>;

	enum DrawType
	{
		DrawIndices,
		DrawVertexs,
	};

	enum MeshType
	{
		PlaneMesh,
		MeshTotal,
	};

	
	class MeshTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		static MeshData *Get(MeshType type);
		static void SetMeshDraw(MeshType pMeshtype, DrawType pDrawtype);
		static void SetMesh(MeshType pMeshtype);
		static void MeshDraw(MeshType pMeshtype, DrawType pDrawtype);

		static void SetMeshDraw(sptrMeshData pMeshData, DrawType pDrawtype);
		static void SetMesh(sptrMeshData pMeshData);
		static void MeshDraw(sptrMeshData pMeshData, DrawType pDrawtype);
		static sptrMeshData CreateMesh(BuffData pVertex, BuffData pIndex);
	protected:

	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;

		static sptrMeshData mPlaneMesh;
	};

	//--
	class MeshData
	{
	public:
		MeshData(BuffData pVdata, BuffData pIdata);
		ID3D11Buffer *GetVetexBuffer()const;
		ID3D11Buffer *GetIndexBuffer()const;
		int GetIndexCnt()const;
		int GetVertexCnt()const;
		int GetStride()const;
		void Release();
	protected:
	private:
		ID3D11Buffer *mVertexBuffer = nullptr;
		ID3D11Buffer *mIndexBuffer = nullptr;
		int mIndexCount;
		int mVertexCount;
		int mVertexStride;
	};
	
}


#endif
