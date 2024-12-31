#ifndef __CONSTANTBUF_H__
#define __CONSTANTBUF_H__

#include "..\GraphicCommon.h"
#include "Typedefs\ConstantBufferType.h"
#include "BufferTool.h"

namespace DX11
{
	template<typename CBstruct>
	class ConstBufData;

	template<typename CBstruct>
	using sptrConstBufData = std::shared_ptr<ConstBufData<CBstruct>>;


	enum ConstantBufType
	{
		Tex2D_ColorAlpha_CB,
		Tex2D_ColorRatioAlpha_CB,
		ConstantBufTotal,
	};


	class ConstantBufTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);

		template<typename CBstruct>
		static ConstBufData<CBstruct> *Get(ConstantBufType type)
		{
			switch (type)
			{
			case DX11::Tex2D_ColorAlpha_CB:
				mTex2DColorAlphaConstBuf.get();
			case DX11::Tex2D_ColorRatioAlpha_CB:
				mTex2DColorRatioAlphaConstBuf.get();
				return 
			case DX11::ConstantBufTotal:
			default:
				g_SysLog->Log(_ERROR, "Error ConstantBufType %d", static_cast<int>(type));
				return nullptr;
			}
		}

		static ID3D11Buffer* GetCBuffer(ConstantBufType type);
		static void *GetCBData(ConstantBufType type);
		static void SetConstantBuf(ConstantBufType type);

		template<typename CBstruct>
		static void SetConstantBuf(sptrConstBufData<CBstruct> pConstBufData)
		{
#if defined(_DEBUG)
			if (!isInitialized)
			{
				g_SysLog->Log(_ERROR, "ConstantBufTool is uninitialized");
				return;
			}
#endif 


			ID3D11Buffer* l_ConstantBuffer = pConstBufData->GetConstantBuffer();
			void *l_data = pConstBufData->GetData();

			mDevContext->UpdateSubresource(l_ConstantBuffer, 0, NULL, l_data, 0, 0);
			mDevContext->VSSetConstantBuffers(0, 1, &l_ConstantBuffer);
			mDevContext->PSSetConstantBuffers(0, 1, &l_ConstantBuffer);
		}

		template<typename CBstruct>
		static sptrConstBufData<CBstruct> CreateConstantBuffer(BuffData pBuffer)
		{
#if defined(_DEBUG)
			if (!isInitialized)
			{
				g_SysLog->Log(_ERROR, "ConstantBufTool is uninitialized");
				return nullptr;
			}
#endif
			if (!BufferTool::CreateBuffer(pBuffer)) return nullptr;

			ConstBufData<CBstruct> *l_data = new ConstBufData<CBstruct>(pBuffer.Buffer);
			return SmartPointer::CreateShared(l_data);
		}

	protected:
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;
		static sptrConstBufData<Tex2D_ColorAlphaCB> mTex2DColorAlphaConstBuf;
		static sptrConstBufData<Tex2D_ColorRatioAlphaCB> mTex2DColorRatioAlphaConstBuf;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename CBstruct>
	class ConstBufData
	{
	public:
		ConstBufData(ID3D11Buffer *pBuffer)
		{
			this->mConstantBuffer = pBuffer;
		}

		ID3D11Buffer *GetConstantBuffer()const
		{
			return mConstantBuffer;
		}
		CBstruct *GetData()
		{
			return &CBData;
		}
		void Release()
		{
			SAFE_RELEASE(mConstantBuffer);
		}

	protected:
	private:
		ID3D11Buffer *mConstantBuffer = nullptr;
		CBstruct CBData;
	};
	//////////////////////////////////////////////////////////////////////////
}

#endif
