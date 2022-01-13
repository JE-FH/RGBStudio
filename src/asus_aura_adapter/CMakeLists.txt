set(HEADER_LIST
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/asus_aura_adapter/ASUSAuraDeviceFactory.hpp"
)

add_library(asus_aura_adapter SHARED 
	"ASUSAuraDeviceFactory.cpp"
	"ASUSAuraKeyboardDevice.cpp"
	"ASUSAuraKeyboardDevice.hpp"
	${HEADER_LIST}
)

target_include_directories(asus_aura_adapter PUBLIC "${UniversalRGBDeviceController_SOURCE_DIR}/include")

target_link_libraries(asus_aura_adapter PUBLIC effect_manager)

target_link_libraries(asus_aura_adapter INTERFACE device_adapter_loader)

target_compile_features(asus_aura_adapter PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)

add_custom_command(
	TARGET asus_aura_adapter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
		$<TARGET_FILE:asus_aura_adapter> 
		"${UniversalRGBDeviceController_SOURCE_DIR}/bin/asus_aura_adapter.dll"
)
