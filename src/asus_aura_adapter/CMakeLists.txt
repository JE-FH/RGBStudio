set(HEADER_LIST
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/asus_aura_adapter/ASUSAuraDeviceFactory.hpp"
)

add_library(asus_aura_adapter STATIC 
	"ASUSAuraDeviceFactory.cpp"
	"ASUSAuraKeyboardDevice.cpp"
	"ASUSAuraKeyboardDevice.hpp"
	${HEADER_LIST}
)

target_include_directories(asus_aura_adapter PUBLIC "${UniversalRGBDeviceController_SOURCE_DIR}/include")

# This should be an INTERFACE dependency since it doesnt need to link effect_manager, 
# it only needs headers. However i dont know if that is correct, so this will work
# for now
target_link_libraries(asus_aura_adapter PUBLIC effect_manager)

target_compile_features(asus_aura_adapter PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
