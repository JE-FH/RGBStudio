set(HEADER_LIST
	"${RGBStudio_SOURCE_DIR}/include/native_effects/FillEffectInstance.hpp"
	"${RGBStudio_SOURCE_DIR}/include/native_effects/FillEffect.hpp"
	"${RGBStudio_SOURCE_DIR}/include/native_effects/FillEffectFactory.hpp"
	"${RGBStudio_SOURCE_DIR}/include/native_effects/VisorEffectInstance.hpp"
	"${RGBStudio_SOURCE_DIR}/include/native_effects/VisorEffect.hpp"
	"${RGBStudio_SOURCE_DIR}/include/native_effects/VisorEffectFactory.hpp"
)

add_library(native_effects STATIC 
	"VisorEffectInstance.cpp"
	"VisorEffect.cpp"
	"VisorEffectFactory.cpp"
	"FillEffectInstance.cpp"
	"FillEffect.cpp"
	"FillEffectFactory.cpp"
	${HEADER_LIST}
)

target_include_directories(native_effects PUBLIC "${RGBStudio_SOURCE_DIR}/include")

target_link_libraries(native_effects PUBLIC effect_manager)
target_link_libraries(native_effects PUBLIC event_trigger_runner)

target_compile_features(native_effects PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
