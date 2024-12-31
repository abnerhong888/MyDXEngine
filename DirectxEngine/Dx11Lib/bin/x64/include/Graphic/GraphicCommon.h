#ifndef __GRAPHICCOMMOM_H__
#define __GRAPHICCOMMOM_H__

#include <d3d11.h>
#include "D3D11sdklayers.h"
#include "DirectXMath.h"
#include "Utility/utility.h"

#define D_FONT_FILE L".\\font\\Arial27.font"


using namespace DirectX;

extern std::shared_ptr<ErrorLogger> g_SysLog;

namespace DX11
{
	using sptrDevice			= std::shared_ptr<ID3D11Device>;
	using sptrDevContext		= std::shared_ptr<ID3D11DeviceContext>;
	using sptrSwpaChain			= std::shared_ptr<IDXGISwapChain>;
	using sptrRenderTargetView	= std::shared_ptr<ID3D11RenderTargetView>;
	using sptrIDXGIFactory		= std::shared_ptr<IDXGIFactory>;
	
	using sptrBuffer			= std::shared_ptr<ID3D11Buffer>;
	using sptrTexture2D			= std::shared_ptr<ID3D11Texture2D>;
	using sptrTexture3D			= std::shared_ptr<ID3D11Texture3D>;
	
}//namespace DX11



#endif