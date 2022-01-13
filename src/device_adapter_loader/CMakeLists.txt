set(HEADER_LIST
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/DeviceFactory.hpp"
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/DeviceFactoryInterface.hpp"
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/APIFunctions.hpp"
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/IKeyboardDevice.hpp"
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/KeyLight.hpp"
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/RGBColor.hpp"
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/ColorUtils.hpp"
	"${RGBStudio_SOURCE_DIR}/include/device_adapter_loader/DeviceAdapter.hpp"
)

add_library(device_adapter_loader STATIC 
	"DeviceFactory.cpp"
	"KeyLight.cpp"
	"DeviceAdapter.cpp"
	${HEADER_LIST}
)

set(device_adapter_loader_API_VERSION 1)

configure_file("constants.hpp.in" "${CMAKE_SOURCE_DIR}/include/device_adapter_loader/constants.g.hpp")

target_include_directories(device_adapter_loader PUBLIC "${RGBStudio_SOURCE_DIR}/include")

target_compile_features(device_adapter_loader PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
