#pragma once
#include "IKeyboardDevice.hpp"
#include "DeviceFactoryInterface.hpp"
#include "DeviceAdapter.hpp"
#include <string>
#include <vector>
#include <memory>

class DeviceFactory {
public:
	DeviceFactory(std::shared_ptr<DeviceAdapter> device_adapter);
	DeviceFactory(const DeviceFactory&) = delete;
	~DeviceFactory();

	std::vector<std::shared_ptr<IKeyboardDevice>> create_devices();
private:
	std::shared_ptr<DeviceAdapter> _device_adapter;
	NativeDeviceFactory* factory_instance;
};