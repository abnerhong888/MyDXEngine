#include "BufferTool.h"

bool DX11::BufferTool::isInitialized = false;;
DX11::sptrDevice DX11::BufferTool::mDevice;
DX11::sptrDevContext DX11::BufferTool::mDevContext;

bool DX11::BufferTool::Initialize(sptrDevice pDevice, sptrDevContext pDevContext)
{
	if (isInitialized) return true;
	if (!pDevice) { g_SysLog->Log(_ERROR, "Device is null"); return false; }
	if (!pDevContext) { g_SysLog->Log(_ERROR, "DevContext is null"); return false; }
	mDevice = pDevice;
	mDevContext = pDevContext;

	isInitialized = true;
	return true;
}

bool DX11::BufferTool::CreateBuffer(BuffData &pBufData)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "BufferTool is uninitialized");
		return false;
	}
#endif
	HRESULT hr = S_OK;
	if(pBufData.Initdata.pSysMem)
		hr = mDevice->CreateBuffer(&pBufData.Desc, &pBufData.Initdata, &pBufData.Buffer);
	else
		hr = mDevice->CreateBuffer(&pBufData.Desc, nullptr, &pBufData.Buffer);
	if (!BufferLog(hr, pBufData)) return false;
	return true;
}

bool DX11::BufferTool::UpdateBufferExample(ID3D11Buffer *pBuf)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "BufferTool is uninitialized");
		return false;
	}
#endif
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT l_hr = mDevContext->Map(pBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	/*
	struct *data = (struct *)mappedResource.pData
	for each 
	{
	data[0].Pos.x = value ...
	}
	*/
	
	mDevContext->Unmap(pBuf, 0);
	return true;
}

bool DX11::BufferTool::CopyBufferToCPUExample(ID3D11Buffer *pBuf)
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "BufferTool is uninitialized");
		return false;
	}
#endif
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT l_hr = mDevContext->Map(pBuf, 0, D3D11_MAP_READ, 0, &mappedResource);
	/*
	struct *data = (struct *)mappedResource.pData
	for each
	{
	cpuMem = data[0].Pos.x;
	}
	*/

	mDevContext->Unmap(pBuf, 0);
	return true;
}

bool DX11::BufferTool::BufferLog(HRESULT hr, BuffData pBufData)
{
	if (FAILED(hr))
	{
		std::string flagsName;
		D3D11_BIND_FLAG flag = static_cast<D3D11_BIND_FLAG>(pBufData.Desc.BindFlags);
		switch (flag)
		{
		case D3D11_BIND_VERTEX_BUFFER:
			flagsName = "VERTEX_BUFFER";
			break;
		case D3D11_BIND_INDEX_BUFFER:
			flagsName = "INDEX_BUFFER";
			break;
		case D3D11_BIND_CONSTANT_BUFFER:
			flagsName = "CONSTANT_BUFFER";
			break;
		case D3D11_BIND_SHADER_RESOURCE:
			flagsName = "SHADER_RESOURCE";
			break;
		case D3D11_BIND_STREAM_OUTPUT:
			flagsName = "STREAM_OUTPUT";
			break;
		case D3D11_BIND_RENDER_TARGET:
			flagsName = "RENDER_TARGET";
			break;
		case D3D11_BIND_DEPTH_STENCIL:
			flagsName = "DEPTH_STENCIL";
			break;
		case D3D11_BIND_UNORDERED_ACCESS:
			flagsName = "UNORDERED_ACCESS";
			break;
		default:
			flagsName = "ERROR_FLAG";
			break;
		}

		std::string str = pBufData.Name + " " + flagsName + " is failed.";
		g_SysLog->Log(_ERROR, str.c_str());
		return false;
	}
	return true;
}