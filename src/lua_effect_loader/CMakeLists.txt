set(HEADER_LIST
	#public headers
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/ILuaValue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaEffect.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaEffectSettings.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaEffect.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaIntegerValue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaNumberValue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaStringValue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaTableValue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaIKeyboardDeviceAdapter.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaTriggerObserverDispatcherAdapter.hpp"
	"${RGBStudio_SOURCE_DIR}/include/lua_effect_loader/LuaUtils.hpp"
)

add_library(lua_effect_loader STATIC 
	"LuaEffectInstance.cpp"
	"LuaEffect.cpp"
	"LuaEffectSettings.cpp"
	"LuaIKeyboardDeviceAdapter.cpp"
	"LuaIntegerValue.cpp"
	"LuaNumberValue.cpp"
	"LuaStringValue.cpp"
	"LuaTableValue.cpp"
	"LuaTriggerObserverDispatcherAdapter.cpp"
	"LuaUtils.cpp"
	"LuaEffectFactory.cpp"
	${HEADER_LIST}
 )

target_include_directories(lua_effect_loader PUBLIC "${RGBStudio_SOURCE_DIR}/include")

target_link_libraries(lua_effect_loader PUBLIC device_adapter_loader)
target_link_libraries(lua_effect_loader PUBLIC effect_manager)
target_link_libraries(lua_effect_loader PUBLIC event_trigger_runner)
target_link_libraries(lua_effect_loader PUBLIC dynamic_config)

find_package(Lua REQUIRED)
target_include_directories(lua_effect_loader PUBLIC ${LUA_INCLUDE_DIR})
target_link_libraries(lua_effect_loader PRIVATE "${LUA_LIBRARIES}")

target_compile_features(lua_effect_loader PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
