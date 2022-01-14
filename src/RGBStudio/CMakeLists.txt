include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(RGBStudio_FRONTEND_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/frontend")
set(ENABLE_INSPECTOR true)

ExternalProject_Add(
	frontend_ts
	DOWNLOAD_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND npx rollup -c "${RGBStudio_FRONTEND_DIRECTORY}/rollup.config.js"
	BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/script/"
	SOURCE_DIR "${RGBStudio_FRONTEND_DIRECTORY}/ts/"
	INSTALL_COMMAND ""
	LOG_BUILD ON
)

add_custom_command(
	OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/build/editor.m.js"
	COMMAND npx rollup -c "${RGBStudio_FRONTEND_DIRECTORY}/rollup.config.js"
	WORKING_DIRECTORY "${RGBStudio_FRONTEND_DIRECTORY}"
	USES_TERMINAL
	DEPENDS
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/editor.m.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/ConnectorType.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/GraphConnection.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/GraphConnector.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/GraphModel.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/GraphNode.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/GraphNodeAttribute.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/GraphSourceConnector.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/GraphTargetConnector.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/NumberAttribute.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/TriggerConnector.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/GraphEditor/TriggerNode.ts"
)

include(${CMAKE_CURRENT_SOURCE_DIR}/helper/setup_ultralight.cmake)

add_executable(
	RGBStudio
		"main.cpp"
		"app.cpp"
		"app.hpp"
)


# Tell MSVC to use main instead of WinMain for Windows subsystem executables
set_target_properties(RGBStudio PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")

# Copy all binaries to target directory
add_custom_command(TARGET RGBStudio POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ULTRALIGHT_BINARY_DIR}" $<TARGET_FILE_DIR:RGBStudio>) 

set(ASSETS_PATH "$<TARGET_FILE_DIR:RGBStudio>/assets") 

# Copy assets to assets path
add_custom_command(TARGET RGBStudio POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/frontend/pages/" "${ASSETS_PATH}")

add_custom_command(TARGET RGBStudio POST_BUILD
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/build/editor.m.js"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/build/" "${ASSETS_PATH}")

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