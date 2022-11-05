set(HEADER_LIST 
	"${RGBStudio_SOURCE_DIR}/include/dynamic_config/IConfigValue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/dynamic_config/IConfigValueTypeDesc.hpp"
	"${RGBStudio_SOURCE_DIR}/include/dynamic_config/ConfigGenericValue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/dynamic_config/DynamicConfig.hpp"
	"${RGBStudio_SOURCE_DIR}/include/dynamic_config/DynamicConfigSpec.hpp"
)

add_library(dynamic_config STATIC 
	"ConfigGenericValue.cpp"
	"DynamicConfig.cpp"
	"DynamicConfigSpec.cpp"
	${HEADER_LIST}
)

target_compile_features(dynamic_config PUBLIC cxx_std_20)

target_link_libraries(dynamic_config INTERFACE device_adapter_loader)

target_include_directories(dynamic_config PUBLIC "${RGBStudio_SOURCE_DIR}/include")

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)