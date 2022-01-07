#pragma once
#include "IKeyboardDevice.h"
#include "LuaUtils.h"
#include <vector>
#include <memory>
class LuaIKeyboardDeviceAdapter
{
public:
	LuaIKeyboardDeviceAdapter(std::shared_ptr<IKeyboardDevice> keyboard_device);
	~LuaIKeyboardDeviceAdapter();

	void push_device(lua_State* L);

	static void openlib(LuaStatePtr& L);

private:
	std::shared_ptr<IKeyboardDevice> _keyboard_device;

	static const char* meta_table_name;
	static const luaL_Reg arraylib_m[];

	std::vector<std::pair<lua_State*, int>> device_references;

	static IKeyboardDevice* check_device(lua_State* L);

	static int lib_fill(lua_State* L);
	static int lib_get_key_count(lua_State* L);
	static int lib_get_key_info(lua_State* L);
	static int lib_get_width(lua_State* L);
	static int lib_get_height(lua_State* L);
	static int lib_set_key_color(lua_State* L);
};

