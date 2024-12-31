#ifndef __BUFFERTOOL_H__
#define __BUFFERTOOL_H__

#include "..\GraphicCommon.h"

namespace DX11
{

	typedef struct _BuffData
	{
		std::string Name;
		D3D11_BUFFER_DESC Desc;
		D3D11_SUBRESOURCE_DATA Initdata;
		ID3D11Buffer *Buffer;
		int BufCounts;
		int BufStride;
		_BuffData() { ZeroMemory(this, sizeof(_BuffData)); }

	}BuffData;

	class BufferTool
	{
	public: 
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		static bool CreateBuffer(BuffData &pBufData);
		static bool UpdateBufferExample(ID3D11Buffer *pBuf);
		static bool CopyBufferToCPUExample(ID3D11Buffer *pBuf);
	protected:
		static bool BufferLog(HRESULT hr, BuffData pBufData);
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;
	};
}



#endif
