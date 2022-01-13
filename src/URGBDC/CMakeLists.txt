add_executable(URGBDC "main.cpp" "KeyTrigger.cpp" "KeyTrigger.hpp")

target_link_libraries(URGBDC PRIVATE effect_manager)
target_link_libraries(URGBDC PRIVATE native_effects)
target_link_libraries(URGBDC PRIVATE lua_effect_loader)
target_link_libraries(URGBDC PRIVATE event_trigger_runner)
target_link_libraries(URGBDC PRIVATE windows_event_sources)
target_link_libraries(URGBDC PRIVATE device_adapter_loader)

target_compile_features(URGBDC PUBLIC cxx_std_20)

add_custom_command(
	TARGET URGBDC POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
		$<TARGET_FILE:URGBDC> 
		"${UniversalRGBDeviceController_SOURCE_DIR}/bin/URGBDC.exe"
)

add_custom_command(
	TARGET URGBDC POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
		"$<TARGET_FILE_DIR:URGBDC>/lua.dll"
		"${UniversalRGBDeviceController_SOURCE_DIR}/bin/lua.dll"
)
