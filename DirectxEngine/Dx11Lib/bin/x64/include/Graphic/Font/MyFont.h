#ifndef __MYFONT_H__
#define __MYFONT_H__

#include "..\GraphicCommon.h"
#include <unordered_map>
#include "..\Tools\TextureTool.h"
#include "..\Tools\ShaderTool.h"
#include "..\Tools\MeshTool.h"
#include "..\Tools\ConstantBufTool.h"
#include "..\Tools\RenderTool.h"
#include "..\Tools\Typedefs\MyColor.h"



namespace DX11
{
	typedef struct _Font_CB
	{
		float posX;
		float posY;
		float fontX;
		float fontY;
		float fontW;
		float fontH;
		float colorR;
		float colorG;
		float colorB;
		float scaleX;
		float scaleY;
		float useless;
		_Font_CB() { ZeroMemory(this, sizeof(_Font_CB)); }

	}Font_CB;

	typedef struct _wordinfo
	{
		float x, y, w, h;
		_wordinfo(float _x, float _y, float _w, float _h) :x(_x), y(_y), w(_w), h(_h) {}
		_wordinfo() { ZeroMemory(this, sizeof(_wordinfo)); }
		_wordinfo &operator= (_wordinfo &in) { memcpy(this, &in, sizeof(_wordinfo)); return *this; }
	}wordinfo;

	typedef struct FontInfo
	{
		std::string BmpName;
		int width = 0;
		int height = 0;
		int fontsize = 0;
		std::string Face;
		std::unordered_map<wchar_t, wordinfo> WordMap;
		FontInfo() { }
		FontInfo &operator = (FontInfo &in) { memcpy(this, &in, sizeof(FontInfo)); return *this; }
	}FontInfo;

	class MyFont
	{
	public:
		MyFont();
		static MyFont &GetIns();
		bool Initialize(
			std::wstring pFontFile,
			sptrDevice pDevice,
			sptrDevContext pDevContext);
		void DrawString(int pPosx, int pPosy, float pFontSize, ColorType pClrtype, const wchar_t *pFmt, ...);
		void DrawStringPush(int pPosx, int pPosy, float pFontSize, ColorType pClrtype, const wchar_t *pFmt, ...);
		FontInfo GetFontInfo();
	protected:
		bool LoadFontFile();

		bool CreateShader(std::wstring pShaderName);
		bool CreateConstantBuffer();
	private:
		bool isInitialized = false;
		sptrShaderData mFontShader;
		sptrConstBufData<Font_CB> mConstBuffer;

		std::wstring mFontFile;
		sptrTexSRV mFontSRV;
		
		FontInfo mFontInfo;

		sptrDevice mDevice;
		sptrDevContext mDevContext;
		wchar_t mTexbuf[256];
	};
}


#endif

