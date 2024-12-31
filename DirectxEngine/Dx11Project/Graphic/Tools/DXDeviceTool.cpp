#include "DXDeviceTool.h"

bool DX11::DXDeviceTool::isInitialized = false;;
DX11::sptrDevice DX11::DXDeviceTool::mDevice;
DX11::sptrDevContext DX11::DXDeviceTool::mDevContext;

bool DX11::DXDeviceTool::initialize(IDXGIAdapter *pAdapter)
{
	if (isInitialized) return true;

	UINT deviceFlag = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	deviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	bool isSuccess = CreateDevice(
		pAdapter,
		featureLevels, 
		numFeatureLevels, 
		driverTypes, 
		numDriverTypes, 
		deviceFlag, 
		&mDevice, 
		&mDevContext);

	isInitialized = isSuccess;
	
	return isSuccess;
}
bool DX11::DXDeviceTool::CreateDevice(
	IDXGIAdapter *pAdapter,
	D3D_FEATURE_LEVEL *featureLevels, UINT numFeatureLevels, 
	D3D_DRIVER_TYPE *driverTypes, UINT numDriverTypes,
	UINT pdeviceFlag,
	sptrDevice *OutDevice, sptrDevContext *OutDevContext)
{

	UINT deviceFlag = pdeviceFlag;

	ID3D11Device *l_Device = nullptr;
	ID3D11DeviceContext *l_DevContex = nullptr;
	bool isSuccess = false;
	// Create the Direct3D Device

	for (UINT drivers = 0; drivers < numDriverTypes; drivers++)
	{
		for (UINT featute = 0; featute < numFeatureLevels; featute++)
		{
			D3D_FEATURE_LEVEL featureLevel = featureLevels[featute];
			D3D_DRIVER_TYPE drivertype = driverTypes[drivers];
			// also can use nullptr adapter and 
			// D3D_DRIVER_TYPE_HARDWARE to create device and swap chain as default
			HRESULT hr = D3D11CreateDevice(
				pAdapter,				//adapter
				drivertype,				//driver
				nullptr,				//software
				deviceFlag,				//deviceFlag
				featureLevels,			//feature level buffer
				numFeatureLevels,		//feature level count
				D3D11_SDK_VERSION,		//SDK version
				&l_Device,				//device
				&featureLevel,			//feature level
				&l_DevContex			//DeviceContext
			);

			if (SUCCEEDED(hr))
			{
				isSuccess = true;
				break;
			}
		} // featute loops

		if (isSuccess)
		{
			break;
		}

	} // drivers loops
	

	if (!isSuccess)
	{
		g_SysLog->Log(_ERROR, "Create Device and DeviceContext is failed.");
		return false;
	}

	*OutDevice = SmartPointer::CreateShared(l_Device);
	*OutDevContext = SmartPointer::CreateShared(l_DevContex);

	return true;
}

DX11::sptrDevice DX11::DXDeviceTool::GetDevice()
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXDeviceTool is uninitialized");
		return nullptr;
	}
#endif
	return mDevice;
}

DX11::sptrDevContext DX11::DXDeviceTool::GetDeviceContext()
{
#if defined(_DEBUG)
	if (!isInitialized)
	{
		g_SysLog->Log(_ERROR, "DXDeviceTool is uninitialized");
		return nullptr;
	}
#endif
	return mDevContext;
}