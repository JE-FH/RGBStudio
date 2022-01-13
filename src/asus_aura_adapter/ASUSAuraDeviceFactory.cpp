#include <asus_aura_adapter/ASUSAuraDeviceFactory.hpp>

#include "ASUSAuraKeyboardDevice.hpp"

#import "libid:F1AA5209-5217-4B82-BA7E-A68198999AFA"
#include <vector>
#include <memory>


struct ASUSAuraDeviceFactory {
	AuraServiceLib::IAuraSdk2Ptr sdk;
};

ASUSAuraDeviceFactoryInitError ASUSAuraDeviceFactory_init(ASUSAuraDeviceFactory** out) {
	auto factory = std::make_unique<ASUSAuraDeviceFactory>();
	factory->sdk = nullptr;

	HRESULT hr = factory->sdk.CreateInstance(__uuidof(AuraServiceLib::AuraSdk), nullptr, CLSCTX_INPROC_SERVER);
	if (!SUCCEEDED(hr))
	{
		return ASUSAuraDeviceFactoryInitError::A_INIT_FAILED;
	}

	hr = factory->sdk->SwitchMode();
	if (!SUCCEEDED(hr)) {
		return ASUSAuraDeviceFactoryInitError::A_CONTROL_DENIED;
	}

	*out = factory.release();
	return ASUSAuraDeviceFactoryInitError::A_NO_ERROR;
}

IKeyboardDevice** ASUSAuraDeviceFactory_create_devices(ASUSAuraDeviceFactory* self) {
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

void ASUSAuraDeviceFactory_free_device_list(IKeyboardDevice** device_list) {
	auto device = std::unique_ptr<IKeyboardDevice* []>(device_list);
}

void ASUSAuraDeviceFactory_free_device(IKeyboardDevice* device) {
	auto a = std::unique_ptr<IKeyboardDevice>(device);
}

void ASUSAuraDeviceFactory_free(ASUSAuraDeviceFactory* self) {
	auto _self = std::unique_ptr<ASUSAuraDeviceFactory>(self);
}