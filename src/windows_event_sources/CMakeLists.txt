set(HEADER_LIST 
	"${RGBStudio_SOURCE_DIR}/include/windows_event_sources/KeyboardEventSource.hpp"
)

add_library(windows_event_sources STATIC 
	"KeyboardEventSource.cpp"
	${HEADER_LIST}
)



target_include_directories(windows_event_sources PUBLIC "${RGBStudio_SOURCE_DIR}/include")

target_link_libraries(windows_event_sources PUBLIC event_trigger_runner)

target_compile_features(windows_event_sources PUBLIC cxx_std_20)


source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
