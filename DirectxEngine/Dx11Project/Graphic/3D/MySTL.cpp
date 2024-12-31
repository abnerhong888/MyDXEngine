#include "MySTL.h"
#include "STLReader.h"


static D3D11_INPUT_ELEMENT_DESC g_STLLayout[] =
{
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/************************************************************************/
/* STL Camera                                                           */
/************************************************************************/

void DX11::STLCamera::RotateByOrth(float pMouseX, float pMouseY, bool pFlag)
{
	static float preX = 0.0f;
	static float preY = 0.0f;

	if (!pFlag)
	{
		preX = pMouseX;
		preY = pMouseY;
	}
	else
	{
		float diffX = pMouseX - preX;
		float diffY = pMouseY - preY;
		float dist = sqrt(diffX*diffX + diffY*diffY);
		if (dist != 0)
		{
			float normx = diffX / dist;
			float normy = diffY / dist;

			XMVECTOR l_Vect = XMVectorSet(normx, normy, 0.0f, 0.0f);
			XMVECTOR l_VectOrth = XMVector3Orthogonal(l_Vect);
			XMVECTOR l_RotAxis = XMQuaternionRotationAxis(l_VectOrth, diffY >= 0 ? D_DEG2RAD(dist) : D_DEG2RAD(dist));
			XMMATRIX l_Rotation = XMMatrixRotationQuaternion(l_RotAxis);

			SetWorldRotation(l_Rotation);

			preX = pMouseX;
			preY = pMouseY;
		}
	}
}

void DX11::STLCamera::CameraOffset(float pMouseX, float pMouseY, bool pFlag)
{
	static float preX = 0.0f;
	static float preY = 0.0f;

	if (!pFlag)
	{
		preX = pMouseX;
		preY = pMouseY;
	}
	else
	{
		float diffX = (pMouseX - preX) / 10;
		float diffY = (pMouseY - preY) / 10;

		SetCamOffset(diffX, diffY, 0.0);
		SetCamTargetOffset(diffX, diffY, 0.0);
		preX = pMouseX;
		preY = pMouseY;
	}
}

void DX11::STLCamera::UpdateConstantBuf(void* pConstbufPtr)
{
	STL_CB *data = (STL_CB *)pConstbufPtr;
	SetWorldPosition(-mCOM[0], -mCOM[1], -mCOM[2]);
	data->World = GetWorld_t();
	data->View = GetView_t();
	data->Projection = GetProjection_t();
	data->Rotation = GetRotation_t();
	data->Light.dir = XMFLOAT3(0.0f, 0.0f, 1.0f);
	data->Light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	data->Light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	data->alpha = 1.0;
}
//////////////////////////////////////////////////////////////////////////

bool DX11::MySTL::Initialize(std::wstring pSTLFile, sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }

	mDevice = pDevice;
	mDevContext = pDevContext;

	mSTLFile = pSTLFile;

	if (!CreateShader(L"STL")) return false;
	if (!CreateMesh()) return false;
	if (!CreateConstantBuffer()) return false;
	
	return true;
}

void DX11::MySTL::InitialCamera(int pWidth, int pHeight)
{
	mSTLCamera.SetCamPosition(0.0, 0.0, 20.0);
	mSTLCamera.SetCamTarget(0.0, 0.0, 0.0);
	mSTLCamera.SetCamUp(0.0, 1.0, 0.0);
	mSTLCamera.SetProjection(pWidth, pHeight, 1, 100);
}

void DX11::MySTL::RenderSTL()
{
	mSTLCamera.UpdateConstantBuf(mSTLConstBuf->GetData());

	RenderTool::SetVertexDataType(TriangleList);
	RenderTool::SetRasterizer(Solid_None);

	// constant buffer
	RenderTool::SetContantBuffer(mSTLConstBuf);
	
	//shader
	RenderTool::SetShader(mSTLShader);
	
	// mesh and draw
#if defined(_DEBUG) || defined(DEBUG)
	RenderTool::SetMeshDraw(mSTLMesh, DrawVertexs);
#else
	RenderTool::SetMeshDraw(mSTLMesh, DrawIndices);
#endif

}

bool DX11::MySTL::CreateShader(std::wstring pShaderName)
{
	mSTLShader = ShaderTool::CreateShader("mSTLShader", pShaderName, g_STLLayout, ARRAYSIZE(g_STLLayout), _shadermodel::g_ShaderModel_5_0);
	if (mSTLShader == nullptr) return false;

	return true;
}

bool DX11::MySTL::CreateMesh()
{
	std::shared_ptr<cSTLReader> l_STLReader = SmartPointer::CreateShared(new cSTLReaderBin());
	std::string l_STLFile = StringConverter::WideToString(mSTLFile);
	
#ifndef _DEBUG
	l_STLReader->FileRead(l_STLFile.c_str(), true);
#else
	l_STLReader->FileRead(l_STLFile.c_str(), false);
#endif

	int l_Vertexs = l_STLReader->getVertexes();
	int l_Indices = l_STLReader->getIndices();
	void* l_VertexBuf = reinterpret_cast<void*>(l_STLReader->getVertexBuffer());
	void* l_IndexBuf = reinterpret_cast<void*>(l_STLReader->getIndexBuffer());

	memcpy(mSTLCamera.mCOM, l_STLReader->getCenterOfMass(), sizeof(float) * 3);
	
	BuffData l_VBufData;
	l_VBufData.Name = l_STLFile + " Mesh";
	l_VBufData.BufCounts = l_Vertexs;
	l_VBufData.BufStride = sizeof(S_STLVertex);
	l_VBufData.Desc.Usage = D3D11_USAGE_DEFAULT;
	l_VBufData.Desc.ByteWidth = sizeof(S_STLVertex) * l_Vertexs;
	l_VBufData.Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	l_VBufData.Desc.CPUAccessFlags = 0;
	l_VBufData.Desc.MiscFlags = 0;
	l_VBufData.Initdata.pSysMem = l_VertexBuf;

	BuffData l_IBufData;

	if (l_IndexBuf)
	{
		l_IBufData.Name = l_STLFile + " Mesh";
		l_IBufData.BufCounts = l_Indices;
		l_IBufData.BufStride = sizeof(DWORD);
		l_IBufData.Desc.Usage = D3D11_USAGE_DEFAULT;
		l_IBufData.Desc.ByteWidth = sizeof(DWORD) * l_Indices;
		l_IBufData.Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		l_IBufData.Desc.CPUAccessFlags = 0;
		l_IBufData.Desc.MiscFlags = 0;
		l_IBufData.Initdata.pSysMem = l_IndexBuf;
	}
	
	mSTLMesh = MeshTool::CreateMesh(l_VBufData, l_IBufData);
	if (mSTLMesh == nullptr) return false;

	return true;
}

bool DX11::MySTL::CreateConstantBuffer()
{
	BuffData l_BufData;
	l_BufData.Name = StringConverter::WideToString(mSTLFile) + " ConstantBuffer";
	l_BufData.Desc.Usage = D3D11_USAGE_DEFAULT;
	l_BufData.Desc.ByteWidth = sizeof(STL_CB);
	l_BufData.Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	l_BufData.Desc.CPUAccessFlags = 0;
	l_BufData.Desc.MiscFlags = 0;
	l_BufData.Initdata.pSysMem = nullptr;

	mSTLConstBuf = ConstantBufTool::CreateConstantBuffer<STL_CB>(l_BufData);
	if (mSTLConstBuf == nullptr) return false;

	//////////////////////////////////////////////////////////////////////////
	return true;
}

void DX11::MySTL::ParseMouseKeyboard(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!MouseKeyBoard::ParseEvent(&mMKB, hWnd, message, wParam, lParam)) return;

	KeyboardClass *keyboard = mMKB.GetKeyboard();
	MouseClass *mouse = mMKB.GetMouse();

	while (!keyboard->CharBufferIsEmpty())
	{
		unsigned char ch = keyboard->ReadChar();
	}

	while (!keyboard->KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard->ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	static bool l_flagL = false;
	static bool l_flagR = false;
	static bool l_flagM = false;
	while (!mouse->EventBufferIsEmpty())
	{
		MouseEvent l_ME = mouse->ReadEvent();
	
		if (l_ME.GetType() == MouseEvent::EventType::WheelUp)
		{
			//gfx.STLCamera.SetWorldOffset(1.0, 0.0, 0.0);
			//gfx.STLCamera.SetCamOffset(0.0, 0.0, 1);
			mSTLCamera.SetWorldScale(1.0, 0.0, 0.0);
			//gfx.STLCamera.Zoom(0.1);
		}

		if (l_ME.GetType() == MouseEvent::EventType::WheelDown)
		{
			//gfx.STLCamera.SetWorldOffset(-1.0, 0.0, 0.0);
			//gfx.STLCamera.SetCamOffset(0.0, 0.0, -1);
			mSTLCamera.SetWorldScale(-1.0, 0.0, 0.0);
			//gfx.STLCamera.Zoom(-0.1);
		}

		if (mouse->IsLeftDown())
		{
			if (!l_flagL)
			{
				if (l_ME.GetPosX() != 0 && l_ME.GetPosY() != 0)
				{
					mSTLCamera.RotateByOrth((float)l_ME.GetPosX(), (float)l_ME.GetPosY(), l_flagL);
					l_flagL = true;
				}
				
			}
			else
			{
				if (l_ME.GetType() == MouseEvent::EventType::Move)
				{
					mSTLCamera.RotateByOrth((float)l_ME.GetPosX(), (float)l_ME.GetPosY(), l_flagL);
				}
			}
		}
		else { l_flagL = false; }
		//----------
		if (mouse->IsRightDown())
		{
			if (!l_flagR)
			{
				if (l_ME.GetPosX() != 0 && l_ME.GetPosY() != 0)
				{
					mSTLCamera.CameraOffset((float)l_ME.GetPosX(), (float)l_ME.GetPosY(), l_flagR);
					l_flagR = true;
				}
			}
			else
			{
				if (l_ME.GetType() == MouseEvent::EventType::Move)
				{
					mSTLCamera.CameraOffset((float)l_ME.GetPosX(), (float)l_ME.GetPosY(), l_flagR);
				}
			}
		}
		else { l_flagR = false; }
		//----------
		if (mouse->IsMiddleDown())
		{
			if (!l_flagM)
			{
				//DXSTLObject::GetInstance().GetMouseClickMiddle(l_ME.GetPosX(), l_ME.GetPosY(), l_flagM);
				l_flagM = true;
			}
			else
			{
				if (l_ME.GetType() == MouseEvent::EventType::Move)
				{
					//DXSTLObject::GetInstance().GetMouseClickMiddle(l_ME.GetPosX(), l_ME.GetPosY(), l_flagM);
				}
			}
		}
		else { l_flagM = false; }
	}
}