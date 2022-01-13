add_executable(effect_system_demo "main.cpp" "KeyTrigger.cpp" "KeyTrigger.hpp")

target_link_libraries(effect_system_demo PRIVATE effect_manager)
target_link_libraries(effect_system_demo PRIVATE native_effects)
target_link_libraries(effect_system_demo PRIVATE lua_effect_loader)
target_link_libraries(effect_system_demo PRIVATE event_trigger_runner)
target_link_libraries(effect_system_demo PRIVATE windows_event_sources)
target_link_libraries(effect_system_demo PRIVATE device_adapter_loader)

target_compile_features(effect_system_demo PUBLIC cxx_std_20)

add_custom_command(
	TARGET effect_system_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
		$<TARGET_FILE:effect_system_demo> 
		"${RGBStudio_SOURCE_DIR}/bin/effect_system_demo.exe"
)

add_custom_command(
	TARGET effect_system_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
		"$<TARGET_FILE_DIR:effect_system_demo>/lua.dll"
		"${RGBStudio_SOURCE_DIR}/bin/lua.dll"
)
