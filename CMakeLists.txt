cmake_minimum_required(VERSION 3.21.1)
project(
	RGBStudio
	VERSION 0.1.0
	LANGUAGES CXX
)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
	message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Find packages go here.

# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system

add_subdirectory("src/device_adapter_loader")
add_subdirectory("src/effect_manager")
add_subdirectory("src/native_effects")
add_subdirectory("src/event_trigger_runner")
add_subdirectory("src/lua_effect_loader")
add_subdirectory("src/windows_event_sources")
add_subdirectory("src/effect_system_demo")

add_subdirectory("src/asus_aura_adapter")