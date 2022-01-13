#pragma once

#include <effect_manager/IKeyboardDevice.hpp>

#include <memory>
#include <cstdint>

//Macros often shadow full caps enums, so we add a prefix
enum class ASUSAuraDeviceFactoryInitError : uint32_t {
	A_NO_ERROR = 0,
	A_INIT_FAILED = 1,
	A_CONTROL_DENIED = 2
};

extern "C" {
	typedef struct ASUSAuraDeviceFactory ASUSAuraDeviceFactory;
	/// <summary>
	/// Creates a new instance of the device factory
	/// </summary>
	/// <param name="out">Out param, pointer to the new factory</param>
	ASUSAuraDeviceFactoryInitError ASUSAuraDeviceFactory_init(ASUSAuraDeviceFactory** out);
	/// <summary>
	/// Creates all devices available from this adapter
	/// </summary>
	/// <returns>Null terminated list of devices allocated by the DLL, this list must be freed with ASUSAuraDeviceFactory_free_device_list</returns>
	IKeyboardDevice** ASUSAuraDeviceFactory_create_devices(ASUSAuraDeviceFactory* self);
	/// <summary>
	/// Frees the list of devices but not the devices themselves
	/// </summary>
	void ASUSAuraDeviceFactory_free_device_list(IKeyboardDevice** device_list);
	/// <summary>
	/// Frees a device created by ASUSAuraDeviceFactory_create_devices
	/// </summary>
	void ASUSAuraDeviceFactory_free_device(IKeyboardDevice* device);
	/// <summary>
	/// Frees, the device factory
	/// </summary>
	void ASUSAuraDeviceFactory_free(ASUSAuraDeviceFactory* self);
}

