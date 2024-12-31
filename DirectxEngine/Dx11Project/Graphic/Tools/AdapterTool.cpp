#include "AdapterTool.h"

bool DX11::DXAdapterTool::isInitialized = false;

std::vector<DX11::sptrAdapter> DX11::DXAdapterTool::mAdapters;

bool DX11::DXAdapterTool::initialize()
{
	if (isInitialized) return true;
	// Emulate Video Cards 
	std::vector<sptrAdapter> l_Adapters = GetAdapters();
	if (mAdapters.size() < 1)
	{
		g_SysLog->Log(_ERROR, "No IDXGI Adapters found.");
		return false;
	}

	isInitialized = true;
	return true;
}

std::vector<DX11::sptrAdapter> DX11::DXAdapterTool::GetAdapters()
{
	if (mAdapters.size() > 0) //If already initialized
		return mAdapters;

	IDXGIFactory *pFactory = nullptr;

	// Create a DXGIFactory object.
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));
	if (FAILED(hr))
	{
		if (g_SysLog)
			g_SysLog->Log(_ERROR, "Failed to create DXGIFactory for enumerating adapters.");
		else
			ErrorLogger::MsgBoxLog("Failed to create DXGIFactory for enumerating adapters.");

		return mAdapters;
	}

	IDXGIAdapter * pAdapter;
	IDXGIOutput * pOutputs;
	UINT index = 0;
	UINT index2 = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		AdapterData *l_ad = new AdapterData(pAdapter);
		sptrAdapter l_sptr = SmartPointer::CreateShared(l_ad);
		mAdapters.push_back(l_sptr);
		index += 1;

		while (SUCCEEDED(pAdapter->EnumOutputs(index2, &pOutputs)))
		{
			mAdapters[index - 1]->mOutputs.push_back(AdapterOutputData(pOutputs));
			index2 += 1;
		}

	}

	SAFE_RELEASE(pFactory);
	
	return mAdapters;
}

std::vector<DX11::sptrAdapter> *DX11::DXAdapterTool::GetAdaptersPtr()
{
	if (mAdapters.size() > 0) //If already initialized
		return &mAdapters;
	else
		return nullptr;
}
IDXGIAdapter* DX11::DXAdapterTool::getGPUAdapter()
{
	IDXGIAdapter *l_adapter = nullptr;
	bool findflag = false;

	for (sptrAdapter data : mAdapters)
	{
		DXGI_ADAPTER_DESC desc = data->mDescription;
		std::wstring wstr(desc.Description);

		findflag |= (wstr.find(L"NVIDIA") != std::wstring::npos);
		findflag |= (wstr.find(L"GeForce") != std::wstring::npos);
		findflag |= (wstr.find(L"AMD") != std::wstring::npos);
		findflag |= (wstr.find(L"Radeon") != std::wstring::npos);

		if (findflag) { l_adapter = data->mAdapter; break; }
		
	}
	return l_adapter;
}

IDXGIAdapter* DX11::DXAdapterTool::getCPUAdapter()
{
	IDXGIAdapter *l_adapter = nullptr;
	bool findflag = false;
	for (sptrAdapter data : mAdapters)
	{
		DXGI_ADAPTER_DESC desc = data->mDescription;
		std::wstring wstr(desc.Description);

		findflag |= (wstr.find(L"Microsoft") != std::wstring::npos);
		if (findflag) {l_adapter = data->mAdapter; break; }
	}

	return l_adapter;
}

DX11::sptrIDXGIFactory DX11::DXAdapterTool::GetDXGIFactory(IDXGIAdapter *pAdapter)
{
	IDXGIFactory *l_Factory = nullptr;
	HRESULT hr = pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&l_Factory));

	if (FAILED(hr))
	{
		if (g_SysLog)
			g_SysLog->Log(_ERROR, "Failed to create DXGIFactory for enumerating adapters.");
		else
			ErrorLogger::MsgBoxLog("Failed to Get Parent of Factory.");
	}


	return SmartPointer::CreateShared(l_Factory);
}

DX11::AdapterData::AdapterData(IDXGIAdapter *pAdapter)
{
	if (!pAdapter) return;
	this->mAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->mDescription);
	if (FAILED(hr))
	{
		ErrorLogger::MsgBoxLog("Failed to Get Description for IDXGIAdapter.");
	}
}

void DX11::AdapterData::Release()
{
	SAFE_RELEASE(mAdapter);
	for (int i = 0; i < mOutputs.size(); i++)
	{
		mOutputs[i].Release();
	}
	mOutputs.clear();
}

DX11::AdapterOutputData::AdapterOutputData(IDXGIOutput *pOutput)
{
	if (!pOutput) return;
	this->mOutput = pOutput;
	HRESULT hr = pOutput->GetDesc(&this->mDescription);
	if (FAILED(hr))
	{
		ErrorLogger::MsgBoxLog("Failed to Get Description for IDXGIOutput.");
	}


}

void DX11::AdapterOutputData::Release()
{
	SAFE_RELEASE(mOutput);
}