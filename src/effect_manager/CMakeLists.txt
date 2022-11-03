set(HEADER_LIST 
	"${RGBStudio_SOURCE_DIR}/include/effect_manager/EffectInstance.hpp"
	"${RGBStudio_SOURCE_DIR}/include/effect_manager/EffectManager.hpp"
)

add_library(effect_manager STATIC "EffectManager.cpp" ${HEADER_LIST})

target_include_directories(effect_manager PUBLIC "${RGBStudio_SOURCE_DIR}/include")

target_link_libraries(effect_manager PUBLIC device_adapter_loader)

target_compile_features(effect_manager PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
