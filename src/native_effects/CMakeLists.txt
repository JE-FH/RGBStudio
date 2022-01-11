set(HEADER_LIST
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/native_effects/FillEffect.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/native_effects/FillEffectFactory.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/native_effects/VisorEffect.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/native_effects/VisorEffectFactory.hpp"
)

add_library(native_effects STATIC 
	"VisorEffect.cpp"
	"VisorEffectFactory.cpp"
	"FillEffect.cpp"
	"FillEffectFactory.cpp"
	${HEADER_LIST}
)

target_include_directories(native_effects PUBLIC "${UniversalRGBDeviceController_SOURCE_DIR}/include")

target_link_libraries(native_effects PUBLIC effect_manager)
target_link_libraries(native_effects PUBLIC event_trigger_runner)

target_compile_features(native_effects PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
