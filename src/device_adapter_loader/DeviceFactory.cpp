#include <device_adapter_loader/DeviceFactory.hpp>
#include <device_adapter_loader/constants.g.hpp>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <iostream>


DeviceFactory::~DeviceFactory() {
	_device_adapter->raw_interface.DeviceFactory_free(factory_instance);
}

DeviceFactory::DeviceFactory(std::shared_ptr<DeviceAdapter> device_adapter)
{
	_device_adapter = std::move(device_adapter);
	factory_instance = nullptr;

	auto error = _device_adapter->raw_interface.DeviceFactory_init(&factory_instance);
	if (error != DeviceFactoryInitError::A_NO_ERROR) {
		switch (error) {
			case DeviceFactoryInitError::A_INIT_FAILED:
				throw std::runtime_error("Device factory init failed for unknown reason");
			case DeviceFactoryInitError::A_CONTROL_DENIED:
				throw std::runtime_error("Device factory init could not get device control");
			default:
				throw std::runtime_error("Invalid DeviceFactoryInitError value");
		}
	}
}

std::vector<std::shared_ptr<IKeyboardDevice>> DeviceFactory::create_devices()
{
	std::vector<std::shared_ptr<IKeyboardDevice>> rv;
	IKeyboardDevice** devices = _device_adapter->raw_interface.DeviceFactory_create_devices(factory_instance);
	for (IKeyboardDevice** it = devices; *it != nullptr; it++) {
		/*
		 * TODO: this might create issues, this lambda has shared ownership of
		 * _device_adapter, however it does not have shared ownership of the device
		 * factory, so if the device relies on the device factory still existing to
		 * deallocate, there is gonna be an error
		 */
		rv.push_back(std::shared_ptr<IKeyboardDevice>(*it, [=](auto p) {
			_device_adapter->raw_interface.Device_free(p);
		}));
	}
	return rv;
}
