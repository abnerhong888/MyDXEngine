#ifndef __ADAPTERREADER_H__
#define __ADAPTERREADER_H__

/************************************************************************/
/* Emulate Video Cards                                                  */
/************************************************************************/

#include "..\GraphicCommon.h"

namespace DX11
{
	class AdapterData;
	using sptrAdapter = std::shared_ptr<AdapterData>;

	class DXAdapterTool
	{
	public:
		static bool initialize();
		static std::vector<sptrAdapter> GetAdapters();
		static std::vector<sptrAdapter> *GetAdaptersPtr();
		static IDXGIAdapter* getGPUAdapter();
		static IDXGIAdapter* getCPUAdapter();

		static sptrIDXGIFactory GetDXGIFactory(IDXGIAdapter *pAdapter);
	private:
		static bool isInitialized;
		static std::vector<sptrAdapter> mAdapters; 
		
	};


	class AdapterOutputData
	{
	public:
		AdapterOutputData(IDXGIOutput *pOutput);
		IDXGIOutput * mOutput = nullptr;
		DXGI_OUTPUT_DESC mDescription;
		void Release();
	};

	class AdapterData
	{
	public:
		AdapterData(IDXGIAdapter * pAdapter);
		IDXGIAdapter * mAdapter = nullptr;
		DXGI_ADAPTER_DESC mDescription;
		std::vector<AdapterOutputData> mOutputs;
		void Release();

	};
}// namespace DX11

#endif // __ADAPTERREADER_H__