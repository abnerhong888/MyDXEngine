#ifndef __DXDEVICETOOL_H__
#define __DXDEVICETOOL_H__

#include "..\GraphicCommon.h"
#include "AdapterTool.h"

namespace DX11
{

	class DXDeviceTool
	{
	public:
		static bool initialize(IDXGIAdapter *pAdapter);
		static bool CreateDevice(
			IDXGIAdapter *pAdapter,
			D3D_FEATURE_LEVEL *featureLevels, UINT numFeatureLevels,
			D3D_DRIVER_TYPE *driverTypes, UINT numDriverTypes,
			UINT pdeviceFlag,
			sptrDevice *OutDevice, sptrDevContext *OutDevContext
	);

		static sptrDevice		GetDevice();
		static sptrDevContext	GetDeviceContext();
	protected:
	private:
		static bool isInitialized;
		static sptrDevice mDevice;
		static sptrDevContext mDevContext;
	};

}


#endif
