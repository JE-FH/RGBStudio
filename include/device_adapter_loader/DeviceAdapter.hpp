#pragma once
#include "IKeyboardDevice.hpp"
#include "DeviceFactoryInterface.hpp"
#include <Windows.h>

struct DeviceAdapterRawInterface {
	DeviceFactory_init_t DeviceFactory_init;
	DeviceFactory_create_devices_t DeviceFactory_create_devices;
	DeviceFactory_free_t DeviceFactory_free;

	DeviceList_free_t DeviceList_free;
	Device_free_t Device_free;

	device_adapter_get_name_t get_name;
	device_adapter_get_api_version_t get_api_version;
};

class DeviceAdapter {
public:
	DeviceAdapter(const char* module_path);
	DeviceAdapter(const DeviceAdapter&) = delete;
	DeviceAdapter(DeviceAdapter&& other);
	~DeviceAdapter();
	const char* get_name();
	DeviceAdapterRawInterface raw_interface;
private:
	HMODULE _module;
};