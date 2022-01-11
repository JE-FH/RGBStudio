#include <lua_effect_loader/LuaNumberValue.hpp>

LuaNumberValue::LuaNumberValue(LUA_NUMBER number)
{
	this->number = number;
}

void LuaNumberValue::push_value(lua_State* L)
{
	lua_pushnumber(L, number);
}
