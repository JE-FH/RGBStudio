#include <asus_aura_adapter/ASUSAuraDeviceFactory.hpp>
#include <device_adapter_loader/constants.g.hpp>

#include <asus_aura_adapter/ASUSAuraDeviceFactory.hpp>
#include "ASUSAuraKeyboardDevice.hpp"

#import "libid:F1AA5209-5217-4B82-BA7E-A68198999AFA"
#include <vector>
#include <memory>


struct NativeDeviceFactory {
	AuraServiceLib::IAuraSdk2Ptr sdk;
};

DeviceFactoryInitError DeviceFactory_init(NativeDeviceFactory** out) {
	auto factory = std::make_unique<NativeDeviceFactory>();
	factory->sdk = nullptr;

	HRESULT hr = factory->sdk.CreateInstance(__uuidof(AuraServiceLib::AuraSdk), nullptr, CLSCTX_INPROC_SERVER);
	if (!SUCCEEDED(hr))
	{
		return DeviceFactoryInitError::A_INIT_FAILED;
	}

	hr = factory->sdk->SwitchMode();
	if (!SUCCEEDED(hr)) {
		return DeviceFactoryInitError::A_CONTROL_DENIED;
	}

	*out = factory.release();
	return DeviceFactoryInitError::A_NO_ERROR;
}

IKeyboardDevice** DeviceFactory_create_devices(NativeDeviceFactory* self) {
	AuraServiceLib::IAuraSyncDeviceCollectionPtr devices = self->sdk->Enumerate(0x00080000);
	std::vector<std::unique_ptr<IKeyboardDevice>> device_list;

	for (int i = 0; i < devices->Count; i++)
	{
		auto found_device = devices->Item[i];
		AuraServiceLib::IAuraSyncKeyboard* pKb;
		HRESULT hr = found_device->QueryInterface(__uuidof(AuraServiceLib::IAuraSyncKeyboard), (void**)&pKb);
		//We will ignore keyboard devices that are not keyboard devices, however a warning system would be cool
		if (SUCCEEDED(hr)) {
			device_list.push_back(std::make_unique<ASUSAuraKeyboardDevice>(pKb));
		}
	}

	auto rv = std::make_unique<IKeyboardDevice* []>(device_list.size() + 1);
	
	for (size_t i = 0; i < device_list.size(); i++) {
		rv[i] = device_list[i].release();
	}

	rv[device_list.size()] = nullptr;
	
	return rv.release();
}

void DeviceFactory_free(NativeDeviceFactory* self) {
	auto _self = std::unique_ptr<NativeDeviceFactory>(self);
}

void DeviceList_free(IKeyboardDevice** device_list) {
	auto device = std::unique_ptr<IKeyboardDevice* []>(device_list);
}

void Device_free(IKeyboardDevice* device) {
	auto a = std::unique_ptr<IKeyboardDevice>(device);
}

const char* device_adapter_get_name()
{
	return "Asus aura adapter";
}

unsigned int device_adapter_get_api_version()
{
	return DEVICE_ADAPTER_API_VERSION;
}
