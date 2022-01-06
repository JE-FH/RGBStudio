#pragma once
#include "IKeyboardDevice.h"
#include "LuaUtils.h"
#include <vector>
class LuaIKeyboardDeviceAdapter
{
public:
	LuaIKeyboardDeviceAdapter(IKeyboardDevice* keyboard_device);
	~LuaIKeyboardDeviceAdapter();

	void push_device(lua_State* L);

	static void openlib(LuaStatePtr& L);

private:
	IKeyboardDevice* _keyboard_device;

	static const char* meta_table_name;
	static const luaL_Reg arraylib_m[];

	std::vector<std::pair<lua_State*, int>> device_references;

	static IKeyboardDevice* check_device(lua_State* L);

	static int lib_fill(lua_State* L);
};

