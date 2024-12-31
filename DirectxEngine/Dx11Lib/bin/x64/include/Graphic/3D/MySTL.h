#ifndef __STL_H__
#define __STL_H__
#include "..\GraphicCommon.h"
#include "..\Tools\ConstantBufTool.h"
#include "..\Tools\ShaderTool.h"
#include "..\Tools\MeshTool.h"
#include "..\Tools\BufferTool.h"
#include "..\Tools\RenderTool.h"
#include "Camera.h"

namespace DX11
{
	/************************************************************************/
	/* STL Camera                                                           */
	/************************************************************************/
	class STLCamera : public Camera
	{
	public:
		void RotateByOrth(float pMouseX, float pMouseY, bool pFlag);
		void CameraOffset(float pMouseX, float pMouseY, bool pFlag);
		void UpdateConstantBuf(void* pConstbufPtr);
		float mCOM[3];
	protected:
	private:
	};

	typedef struct sLight
	{
		XMFLOAT3 dir;
		float useless;
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		sLight() { ZeroMemory(this, sizeof(sLight)); }

	}sLight;

	typedef struct STL_CB
	{
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Projection;
		XMMATRIX Rotation;
		sLight Light;
		float alpha;
		float COM[3]; //center of mass
		STL_CB() { ZeroMemory(this, sizeof(STL_CB)); }

	}STL_CB;


	class MySTL
	{
	public:
		bool Initialize(
			std::wstring pSTLFile,
			sptrDevice pDevice,
			sptrDevContext pDevContext);
		void InitialCamera(int pWidth, int pHeight);
		void RenderSTL();
		void ParseMouseKeyboard(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		STLCamera mSTLCamera;
	protected:
		bool CreateShader(std::wstring pShaderName);
		bool CreateMesh();
		bool CreateConstantBuffer();
	private:

		sptrDevice mDevice;
		sptrDevContext mDevContext;

		sptrShaderData mSTLShader;
		sptrMeshData mSTLMesh;
		sptrConstBufData<STL_CB> mSTLConstBuf;

		std::wstring mSTLFile = L"";
		MouseKeyBoard mMKB;
	};


}

#endif
