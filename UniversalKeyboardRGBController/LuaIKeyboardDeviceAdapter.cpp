#include "LuaIKeyboardDeviceAdapter.h"

const char* LuaIKeyboardDeviceAdapter::meta_table_name = "UniversalKeyboardRGBController.LuaIKeyboardDeviceAdapter";
const luaL_Reg LuaIKeyboardDeviceAdapter::arraylib_m[] = {
	{"fill", LuaIKeyboardDeviceAdapter::lib_fill},
	{"get_key_count", LuaIKeyboardDeviceAdapter::lib_get_key_count},
	{"get_key_info", LuaIKeyboardDeviceAdapter::lib_get_key_info},
	{"get_width", LuaIKeyboardDeviceAdapter::lib_get_width},
	{"get_height", LuaIKeyboardDeviceAdapter::lib_get_height},
	{"set_key_color", LuaIKeyboardDeviceAdapter::lib_set_key_color},
	{NULL, NULL}
};


LuaIKeyboardDeviceAdapter::LuaIKeyboardDeviceAdapter(std::shared_ptr<IKeyboardDevice> keyboard_device)
{
	_keyboard_device = std::move(keyboard_device);
}

LuaIKeyboardDeviceAdapter::~LuaIKeyboardDeviceAdapter()
{
	for (auto& ref : device_references) {
		lua_rawgeti(ref.first, LUA_REGISTRYINDEX, ref.second);
		IKeyboardDevice** ud = (IKeyboardDevice**)luaL_checkudata(ref.first, -1, meta_table_name);
		*ud = nullptr;
		luaL_unref(ref.first, LUA_REGISTRYINDEX, ref.second);
		lua_pop(ref.first, 1);
	}
}

void LuaIKeyboardDeviceAdapter::push_device(lua_State* L)
{
	lua_newuserdata(L, sizeof(IKeyboardDevice*));
	luaL_getmetatable(L, meta_table_name);
	lua_setmetatable(L, -2);

	IKeyboardDevice** ud = (IKeyboardDevice**) luaL_checkudata(L, -1, meta_table_name);
	*ud = _keyboard_device.get();

	int ref = luaL_ref(L, LUA_REGISTRYINDEX);

	device_references.push_back(std::pair(L, ref));

	lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

	luaL_getmetatable(L, meta_table_name);
	lua_setmetatable(L, -2);
}

void LuaIKeyboardDeviceAdapter::openlib(LuaStatePtr& L)
{
	luaL_newmetatable(L, meta_table_name);

	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, arraylib_m, 0);

	lua_pop(L, 1);
}

IKeyboardDevice* LuaIKeyboardDeviceAdapter::check_device(lua_State* L)
{
	IKeyboardDevice** ud = (IKeyboardDevice**) luaL_checkudata(L, 1, meta_table_name);
	luaL_argcheck(L, ud != nullptr, 1, "device expected");
	luaL_argcheck(L, *ud != nullptr, 1, "device has been invalidated (cannot be used after draw call returned)");

	return *ud;
}

int LuaIKeyboardDeviceAdapter::lib_fill(lua_State* L)
{
	IKeyboardDevice* device = check_device(L);

	lua_Integer r = luaL_checkinteger(L, 2);
	luaL_argcheck(L, r >= 0 && r <= 255, 2, "color value has to be between 0 and 255 inclusively");
	
	lua_Integer g = luaL_checkinteger(L, 3);
	luaL_argcheck(L, g >= 0 && g <= 255, 3, "color value has to be between 0 and 255 inclusively");
	
	lua_Integer b = luaL_checkinteger(L, 4);
	luaL_argcheck(L, b >= 0 && b <= 255, 4, "color value has to be between 0 and 255 inclusively");

	device->fill(RGBColor{ (unsigned char)r, (unsigned char)g, (unsigned char)b });

	return 0;
}

int LuaIKeyboardDeviceAdapter::lib_get_key_count(lua_State* L)
{
	IKeyboardDevice* device = check_device(L);

	lua_pushinteger(L, device->key_end() - device->key_begin());

	return 1;
}

int LuaIKeyboardDeviceAdapter::lib_get_key_info(lua_State* L)
{
	IKeyboardDevice* device = check_device(L);
	
	auto key_begin = device->key_begin();
	auto key_end = device->key_end();

	long long key_count = key_end - key_begin;
	
	lua_Integer index = luaL_checkinteger(L, 2);
	luaL_argcheck(L, index < key_count, 2, "index is out of range");

	auto target_key = device->key_begin() + index;

	lua_createtable(L, 0, 3);

	lua_pushstring(L, "code");
	lua_pushinteger(L, (*target_key)->code);
	lua_settable(L, -3);

	lua_pushstring(L, "x");
	lua_pushnumber(L, (*target_key)->x);
	lua_settable(L, -3);

	lua_pushstring(L, "y");
	lua_pushnumber(L, (*target_key)->y);
	lua_settable(L, -3);

	return 1;
}

int LuaIKeyboardDeviceAdapter::lib_get_width(lua_State* L)
{
	IKeyboardDevice* device = check_device(L);

	lua_pushnumber(L, device->get_width());
	return 1;
}

int LuaIKeyboardDeviceAdapter::lib_get_height(lua_State* L)
{
	IKeyboardDevice* device = check_device(L);

	lua_pushnumber(L, device->get_height());
	return 0;
}

int LuaIKeyboardDeviceAdapter::lib_set_key_color(lua_State* L)
{
	IKeyboardDevice* device = check_device(L);
	
	auto key_begin = device->key_begin();
	auto key_end = device->key_end();

	long long key_count = key_end - key_begin;

	lua_Integer index = luaL_checkinteger(L, 2);
	luaL_argcheck(L, index < key_count, 2, "index is out of range");

	auto target_key = device->key_begin() + index;

	lua_Integer r = luaL_checkinteger(L, 3);
	luaL_argcheck(L, r >= 0 && r <= 255, 3, "color value has to be between 0 and 255 inclusively");

	lua_Integer g = luaL_checkinteger(L, 4);
	luaL_argcheck(L, g >= 0 && g <= 255, 4, "color value has to be between 0 and 255 inclusively");

	lua_Integer b = luaL_checkinteger(L, 5);
	luaL_argcheck(L, b >= 0 && b <= 255, 5, "color value has to be between 0 and 255 inclusively");

	(*target_key)->set_color(RGBColor{ (unsigned char)r,(unsigned char)g, (unsigned char)b });

	return 0;
}
