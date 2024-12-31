#ifndef __SHADER_H__
#define __SHADER_H__

#include "..\GraphicCommon.h"

namespace DX11
{
	class ShaderData;
	using sptrShaderData = std::shared_ptr<ShaderData>;

	typedef struct ShaderModel
	{
		std::string VertexModel, PixelModel, VertexEntryPoint, PixelEntryPoint;
		ShaderModel() { ZeroMemory(this, sizeof(ShaderModel)); }
		ShaderModel(std::string VEntry, std::string PEntry, std::string Version)
		{
			ZeroMemory(this, sizeof(ShaderModel));
			VertexEntryPoint = VEntry;PixelEntryPoint = PEntry;
			VertexModel = "vs_" + Version;PixelModel = "ps_" + Version;
		}
		ShaderModel &operator= (ShaderModel &in){memcpy(this, &in, sizeof(ShaderModel));return *this;}

	}ShaderModel;


	namespace _shadermodel
	{
		static const ShaderModel g_ShaderModel_5_0("VS", "PS", "5_0");
		static const ShaderModel g_ShaderModel_4_0("VS", "PS", "4_0");
	}

	enum ShaderTpye
	{
		Tex2D,
		Tex2D_ColorAlpha,
		Tex2D_ColorRatioAlpha,
		Tex3D,
		ShaderTotal,
	};

	class ShaderTool
	{
	public:
		static bool Initialize(sptrDevice pDevice, sptrDevContext pDevContext);
		static ShaderData *Get(ShaderTpye type);
		static void SetShader(ShaderTpye type);
		static void SetShader(sptrShaderData pShaderData);
		static sptrShaderData CreateShader(std::string pName,
			std::wstring pShaderName,
			D3D11_INPUT_ELEMENT_DESC *pLayout,
			UINT NumElements,
			ShaderModel pShaderModel);

		static bool CheckFeatureLevel(ShaderModel pShaderModel);
	protected:
		void ClearCompliedShader();
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;

		static sptrShaderData mTex2D;
		static sptrShaderData mTex2D_ColorAlpha;
		static sptrShaderData mTex2D_ColorRatioAlpha;
		static sptrShaderData mTex3D;
		
	};

	class ShaderData
	{
	public:
		ShaderData(
			ID3D11VertexShader *pVshader,
			ID3D10Blob *pVbuffer,
			ID3D11PixelShader *pPshader,
			ID3D10Blob *pPbuffer, 
			ID3D11InputLayout *pInputLauout,
			std::wstring pFileName);

		ID3D11VertexShader *GetVertexShader() const;
		ID3D11PixelShader *GetPixelShader() const;
		ID3D11InputLayout *GetInputLayout() const;
		ID3D10Blob *GetPixelShaderBuffer() const;
		ID3D10Blob *GetVertexShaderBuffer() const;
		std::wstring GetShaderFileName() const;
		void Release();
	protected:
	private:
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D10Blob* mVertexShaderBuffer = nullptr;

		ID3D11PixelShader* mPixelShader = nullptr;
		ID3D10Blob* mPixelShaderBuffer = nullptr;

		ID3D11InputLayout* mInputLayout = nullptr;
		std::wstring mFileName;
	};

	

	class ShaderCreator
	{
	public:
		struct shdata
		{
			ID3D11VertexShader* VShader;
			ID3D10Blob* VBuffer;
			ID3D11PixelShader* PShader;
			ID3D10Blob* PBuffer;
			ID3D11InputLayout* InputLayout;
			D3D11_INPUT_ELEMENT_DESC *Layout;
			UINT NumLayouts;
		};

		static bool _CreaterShader(
			sptrDevice pDevice,
			D3D11_INPUT_ELEMENT_DESC *Layout,
			UINT NumElements,
			ShaderModel pModel,
			std::wstring pShaderName,
			ShaderData **pShaderData
		);

		static std::shared_ptr<ErrorLogger> mShaderLogger;
	protected:
		static bool FXShaderCompiler(shdata &pshdata);
		static bool CompilerShaderFile(shdata &pshdata, std::string Type);
		static bool LoadShaderBinFile(shdata &pshdata);
		static bool Create(shdata &pshdata);
		static bool SaveToBinaryFile(shdata &pshdata, std::wstring pFileName);

		
	private:
		static sptrDevice mDevice;
		static ShaderData *mShaderData;
		static ShaderModel *mShaderModel;
		static std::wstring mFileName;
	};

}



#endif