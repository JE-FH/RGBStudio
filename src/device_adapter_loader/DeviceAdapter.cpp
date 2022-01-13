#include <device_adapter_loader/DeviceAdapter.hpp>
#include <device_adapter_loader/constants.g.hpp>
#include <stdexcept>
#include <iostream>

const char* DeviceFactory_init_pn = "DeviceFactory_init";
const char* DeviceFactory_create_devices_pn = "DeviceFactory_create_devices";
const char* DeviceFactory_free_pn = "DeviceFactory_free";
const char* DeviceList_free_pn = "DeviceList_free";
const char* Device_free_pn = "Device_free";
const char* device_adapter_get_name_pn = "device_adapter_get_name";
const char* device_adapter_get_api_version_pn = "device_adapter_get_api_version";

template<typename T>
T get_func_or_throw(HMODULE mod, const char* name) {
	T func = (T)GetProcAddress(mod, name);
	if (func == nullptr) {
		throw std::runtime_error("Invalid module, could not get function: " + std::string(name));
	}
	return (T)GetProcAddress(mod, name);
}

std::string GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string(); //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}


DeviceAdapter::DeviceAdapter(const char* module_path) {
	_module = LoadLibrary(module_path);

	if (_module == nullptr) {
		std::cout << GetLastErrorAsString() << std::endl;
		throw std::runtime_error("Could not load specified dll: " + std::string(module_path));
	}

	raw_interface.DeviceFactory_init = get_func_or_throw<DeviceFactory_init_t>(_module, DeviceFactory_init_pn);
	raw_interface.DeviceFactory_create_devices = get_func_or_throw<DeviceFactory_create_devices_t>(_module, DeviceFactory_create_devices_pn);
	raw_interface.DeviceFactory_free = get_func_or_throw<DeviceFactory_free_t>(_module, DeviceFactory_free_pn);
	raw_interface.DeviceList_free = get_func_or_throw<DeviceList_free_t>(_module, DeviceList_free_pn);
	raw_interface.Device_free = get_func_or_throw<Device_free_t>(_module, Device_free_pn);
	raw_interface.get_name = get_func_or_throw<device_adapter_get_name_t>(_module, device_adapter_get_name_pn);
	raw_interface.get_api_version = get_func_or_throw<device_adapter_get_api_version_t>(_module, device_adapter_get_api_version_pn);
	
	unsigned int version = raw_interface.get_api_version();
	if (version != DEVICE_ADAPTER_API_VERSION) {
		FreeModule(_module);
		_module = nullptr;
		throw std::runtime_error("Incompatible device adapter module");
	}
}

DeviceAdapter::DeviceAdapter(DeviceAdapter&& other) {
	_module = std::move(other._module);
	raw_interface = std::move(other.raw_interface);
	other._module = nullptr;
}

DeviceAdapter::~DeviceAdapter() {
	if (_module != nullptr) {
		FreeModule(_module);
		_module = nullptr;
	}
}

const char* DeviceAdapter::get_name()
{
	return raw_interface.get_name();
}
