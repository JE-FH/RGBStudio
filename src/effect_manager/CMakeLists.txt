set(HEADER_LIST 
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/effect_manager/Effect.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/effect_manager/EffectManager.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/effect_manager/IKeyboardDevice.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/effect_manager/IKeyLight.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/effect_manager/RGBColor.hpp"
)

add_library(effect_manager STATIC "EffectManager.cpp" ${HEADER_LIST})

target_include_directories(effect_manager PUBLIC "${UniversalRGBDeviceController_SOURCE_DIR}/include")

target_compile_features(effect_manager PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
