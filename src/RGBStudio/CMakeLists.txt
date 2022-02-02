set(RGBStudio_FRONTEND_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/frontend")

add_executable(
	RGBStudio
	"main.cpp"
	"editor.cpp"
	"IAssetLoader.hpp"
	"FSAssetLoader.cpp"
	"FSAssetLoader.hpp"
	"EncodingConverter.hpp"
	"EncodingConverter.cpp"
	"JSONRPC.hpp"
	"JSONRPC.cpp"
)

find_program(NUGET_EXE NAMES nuget)
if(NOT NUGET_EXE)
	message(FATAL_ERROR "nuget.exe not found")
endif()

exec_program(${NUGET_EXE}
    ARGS install "Microsoft.Web.WebView2" -Version 1.0.1072.54 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages
)

exec_program(${NUGET_EXE}
    ARGS install "Microsoft.Windows.ImplementationLibrary" -Version 1.0.211019.2 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages
)

target_link_libraries(RGBStudio PRIVATE "${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2/build/native/Microsoft.Web.WebView2.targets")
target_link_libraries(RGBStudio PRIVATE "${CMAKE_BINARY_DIR}/packages/Microsoft.Windows.ImplementationLibrary/build/native/Microsoft.Windows.ImplementationLibrary.targets")
target_link_libraries(RGBStudio PUBLIC event_trigger_runner)

#Visual studio and vscode does not understand the include directories from .targets so we hardcode them

target_include_directories(RGBStudio PRIVATE "${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2/build/native/include/")
target_include_directories(RGBStudio PRIVATE "${CMAKE_BINARY_DIR}/packages/Microsoft.Windows.ImplementationLibrary/include/")

target_compile_features(RGBStudio PUBLIC cxx_std_20)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(RGBStudio PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

set(ASSETS_PATH "$<TARGET_FILE_DIR:RGBStudio>/assets") 

add_custom_target(
	frontend_build
	COMMAND nmake /NOLOGO /C "all"
	WORKING_DIRECTORY ${RGBStudio_FRONTEND_DIRECTORY}
	USES_TERMINAL
	SOURCES
		"${RGBStudio_FRONTEND_DIRECTORY}/ts/editor.m.ts"
		"${RGBStudio_FRONTEND_DIRECTORY}/less/editor.less"
 "JSONRPC.hpp")

add_custom_command(TARGET frontend_build POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E rm -r "${ASSETS_PATH}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/build/" "${ASSETS_PATH}")



add_dependencies(RGBStudio frontend_build)
