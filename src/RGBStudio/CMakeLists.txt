include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(RGBStudio_FRONTEND_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/frontend")
set(ENABLE_INSPECTOR true)

include(${CMAKE_CURRENT_SOURCE_DIR}/helper/setup_ultralight.cmake)

add_executable(
	RGBStudio
		"main.cpp"
		"app.cpp"
		"app.hpp"
)

set(ASSETS_PATH "$<TARGET_FILE_DIR:RGBStudio>/assets") 

# Tell MSVC to use main instead of WinMain for Windows subsystem executables
set_target_properties(RGBStudio PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")

# Copy all binaries to target directory
add_custom_command(TARGET RGBStudio POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_BINARY_DIR}" $<TARGET_FILE_DIR:RGBStudio>) 

# Copy assets to assets path
add_custom_command(TARGET RGBStudio POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/frontend/pages/" "${ASSETS_PATH}")

if(${ENABLE_INSPECTOR})
  # Copy inspector to assets directory
  add_custom_command(TARGET RGBStudio POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_INSPECTOR_DIR}" "${ASSETS_PATH}/inspector")
endif ()

# Copy resources to assets directory
add_custom_command(TARGET RGBStudio POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_RESOURCES_DIR}" "${ASSETS_PATH}/resources")
  
add_dependencies(RGBStudio UltralightSDK)


target_compile_features(RGBStudio PUBLIC cxx_std_20)

add_custom_target(
	frontend_build
	COMMAND nmake /NOLOGO /C
	WORKING_DIRECTORY ${RGBStudio_FRONTEND_DIRECTORY}
	USES_TERMINAL
	SOURCES
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/editor.m.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/less/editor.less"
)

add_custom_command(TARGET frontend_build POST_BUILD
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/build/editor.m.js"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/build/" "${ASSETS_PATH}")

add_dependencies(RGBStudio frontend_build)
