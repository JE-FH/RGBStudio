add_executable(URGBDC "main.cpp" "KeyTrigger.cpp" "KeyTrigger.hpp")

target_link_libraries(URGBDC PRIVATE effect_manager)
target_link_libraries(URGBDC PRIVATE asus_aura_adapter)
target_link_libraries(URGBDC PRIVATE native_effects)
target_link_libraries(URGBDC PRIVATE lua_effect_loader)
target_link_libraries(URGBDC PRIVATE event_trigger_runner)
target_link_libraries(URGBDC PRIVATE windows_event_sources)

target_compile_features(asus_aura_adapter PUBLIC cxx_std_20)