#include "ASUSAuraDeviceFactory.h"
#include <exception>

ASUSAuraDeviceFactory::ASUSAuraDeviceFactory()
{
	HRESULT hr;
	// Initialize COM
	hr = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (!SUCCEEDED(hr))
	{
		// Uninitialize COM
		::CoUninitialize();
		throw std::exception("Could not initialize COM");
	}

	_sdk = nullptr;
	hr = _sdk.CreateInstance(__uuidof(AuraServiceLib::AuraSdk), nullptr, CLSCTX_INPROC_SERVER);

	if (!SUCCEEDED(hr))
	{
		// Uninitialize COM
		::CoUninitialize();
		throw std::exception("Could not create aura sdk instance");
	}

	_sdk->SwitchMode();
}

ASUSAuraDeviceFactory::~ASUSAuraDeviceFactory()
{
}

std::unique_ptr<ASUSAuraKeyboardDevice> ASUSAuraDeviceFactory::create_keyboard_device()
{
	AuraServiceLib::IAuraSyncDeviceCollectionPtr devices = _sdk->Enumerate(0x00080000);
	for (int i = 0; i < devices->Count; i++)
	{
		auto found_device = devices->Item[i];
		AuraServiceLib::IAuraSyncKeyboard* pKb;
		HRESULT hr = found_device->QueryInterface(__uuidof(AuraServiceLib::IAuraSyncKeyboard), (void**)&pKb);

		if (!SUCCEEDED(hr)) {
			throw std::exception("Could not get IAuraSyncKeyboard from keyboard device");
		}

		return std::make_unique<ASUSAuraKeyboardDevice>(pKb);
	}
	return std::unique_ptr<ASUSAuraKeyboardDevice>(nullptr);
}
