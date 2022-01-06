#include "LuaNumberValue.h"

LuaNumberValue::LuaNumberValue(LUA_NUMBER number)
{
	this->number = number;
}

void LuaNumberValue::push_value(lua_State* L)
{
	lua_pushnumber(L, number);
}
