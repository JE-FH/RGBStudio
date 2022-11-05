add_executable(RGBLightRunner "main.cpp" "Program.cpp" "Program.hpp")

target_link_libraries(RGBLightRunner PRIVATE effect_manager)
target_link_libraries(RGBLightRunner PRIVATE native_effects)
target_link_libraries(RGBLightRunner PRIVATE lua_effect_loader)
target_link_libraries(RGBLightRunner PRIVATE event_trigger_runner)
target_link_libraries(RGBLightRunner PRIVATE windows_event_sources)
target_link_libraries(RGBLightRunner PRIVATE device_adapter_loader)
target_link_libraries(RGBLightRunner PRIVATE dynamic_config)

target_compile_features(RGBLightRunner PUBLIC cxx_std_20)

find_package(rpclib CONFIG REQUIRED)
target_link_libraries(RGBLightRunner PRIVATE rpclib::rpc)

add_custom_command(
	TARGET RGBLightRunner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
		$<TARGET_FILE:RGBLightRunner> 
		"${RGBStudio_SOURCE_DIR}/bin/RGBLightRunner.exe"
)