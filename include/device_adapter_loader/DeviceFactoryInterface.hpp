#pragma once
#include <cstdint>
#include "IKeyboardDevice.hpp"

//Macros often shadow full caps enums, so we add a prefix
enum class DeviceFactoryInitError : uint32_t {
	A_NO_ERROR = 0,
	A_INIT_FAILED = 1,
	A_CONTROL_DENIED = 2
};


extern "C" {
	typedef struct NativeDeviceFactory NativeDeviceFactory;

	typedef DeviceFactoryInitError(*DeviceFactory_init_t)(NativeDeviceFactory** out);
	typedef IKeyboardDevice** (*DeviceFactory_create_devices_t)(NativeDeviceFactory* self);
	typedef void (*DeviceFactory_free_t)(NativeDeviceFactory* self);
	typedef void (*DeviceList_free_t)(IKeyboardDevice** device_list);
	typedef void (*Device_free_t)(IKeyboardDevice* device);
	typedef const char* (*device_adapter_get_name_t)();
	typedef unsigned int (*device_adapter_get_api_version_t)();
}