
extern "C" {
	/// <summary>
	/// Creates a new instance of the device factory
	/// </summary>
	/// <param name="out">Out param, pointer to the new factory</param>
	__declspec(dllexport) DeviceFactoryInitError DeviceFactory_init(NativeDeviceFactory** out);
	/// <summary>
	/// Creates all devices available from this adapter
	/// </summary>
	/// <returns>Null terminated list of devices allocated by the DLL, this list must be freed with ASUSAuraDeviceFactory_free_device_list</returns>
	__declspec(dllexport) IKeyboardDevice** DeviceFactory_create_devices(NativeDeviceFactory* self);
	/// <summary>
	/// Frees, the device factory
	/// </summary>
	__declspec(dllexport) void DeviceFactory_free(NativeDeviceFactory* self);

	/// <summary>
	/// Frees the list of devices but not the devices themselves
	/// </summary>
	__declspec(dllexport) void DeviceList_free(IKeyboardDevice** device_list);

	/// <summary>
	/// Frees a device created by ASUSAuraDeviceFactory_create_devices
	/// </summary>
	__declspec(dllexport) void Device_free(IKeyboardDevice* device);

	/// <summary>
	/// Gets the name of this device adapter, should be unique to the device type,
	/// eg. dont name this icue if you are making a asus aura adapter
	/// </summary>
	__declspec(dllexport) const char* device_adapter_get_name();

	/// <summary>
	/// Gets the API version this device adapter was made for
	/// </summary>
	__declspec(dllexport) unsigned int device_adapter_get_api_version();
}
