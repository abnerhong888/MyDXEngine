#ifndef __TEXTURECREATOR_H__
#define __TEXTURECREATOR_H__

#include "..\GraphicCommon.h"
#include "WICTextureLoader.h"
namespace DX11
{
	enum TextureType
	{
		RENDER_SRV_TARGET,
		CopyGPU2CPU,
		SRV_GPU_R_CPU_W,
		TexTypeDefault,
	};

	enum TextureFormat
	{
		RGBA16_U	= DXGI_FORMAT_R16G16B16A16_UNORM,
		RGBA8_U		= DXGI_FORMAT_R8G8B8A8_UNORM,
		R16_U		= DXGI_FORMAT_R16_UNORM,
		R8_U		= DXGI_FORMAT_R8_UNORM,
		
	};

	typedef struct TexSRV
	{
	public:
		ID3D11ShaderResourceView *SRV;
		ID3D11Resource *Resource;
		TexSRV(): SRV(nullptr), Resource(nullptr){}
		TexSRV(ID3D11ShaderResourceView *_SRV, ID3D11Resource *_Resource) : SRV(_SRV), Resource(_Resource) {}
		void Release() { SAFE_RELEASE(SRV); SAFE_RELEASE(Resource); }
	}TexSRV;

	using sptrTexSRV = std::shared_ptr<TexSRV>;

	class TextureTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		// 2D
		static bool CreateRTV_2D(std::string pName, ID3D11Resource *pTex, ID3D11RenderTargetView **pOutRTV);
		static bool CreateSRV_2D(std::string pName, ID3D11Resource *pTex, TextureFormat pFormat, ID3D11ShaderResourceView **pOutSRV);

		static bool CreateTexRGBA_2D(
			std::string pName, int pWidth , int pHeight, 
			TextureType pType,
			TextureFormat pFormat,
			ID3D11Resource **pOutTex);

		static sptrTexSRV CreateSRVFromFile_2D(std::wstring pFileName);
		static sptrTexSRV CreateTexRGBASRV_2D(std::string pName, int pWidth, int pHeight, TextureType pType, TextureFormat pTexFormat);

		static bool CopyTexToCPU_2D(std::string pName, ID3D11Resource *pTex, BYTE *CpuMem);
		static void CopyTexToTex_2D(ID3D11Resource *pSrcTex, ID3D11Resource *pDstTex);
		static void CopyTexAreaToTex_2D(ID3D11Resource *pSrcTex, ID3D11Resource *pDstTex, D3D11_BOX pBox, int pDstX, int pDstY, int pDstZ);
		static bool UpdateTex_2D(std::string pName, ID3D11Resource *pTex, void *pData, int pDataW, int pDataH, TextureFormat pFormat);
		
		// 3D
		static bool CreateRTV_3D(std::string pName, ID3D11Resource *pTex, ID3D11RenderTargetView **pOutRTV);
		static bool CreateSRV_3D(std::string pName, ID3D11Resource *pTex, TextureFormat pFormat, ID3D11ShaderResourceView **pOutSRV);
		static bool CreateTexRGBA_3D(
			std::string pName, int pWidth, int pHeight, int pDepth,
			TextureType pType,
			TextureFormat pFormat,
			ID3D11Resource **pOutTex);
		static sptrTexSRV CreateSRVFromFile_3D(std::wstring pFileName);
		static bool CopyTexToCPU_3D(std::string pName, ID3D11Resource *pTex, BYTE *CpuMem);
		static void CopyTexToTex_3D(ID3D11Resource *pSrcTex, ID3D11Resource *pDstTex);
		static bool UpdateTex_3D(std::string pName, ID3D11Resource *pTex, void *pData, int pDataW, int pDataH, int pDataD, TextureFormat pFormat);
	protected:
		static int GetFotmatByteSize(DXGI_FORMAT pFormat);
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;
	};
}


#endif
