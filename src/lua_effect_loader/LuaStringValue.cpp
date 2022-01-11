#include <lua_effect_loader/LuaStringValue.hpp>

LuaStringValue::LuaStringValue(std::string str)
{
	this->str = std::move(str);
}

void LuaStringValue::push_value(lua_State* L)
{
	lua_pushlstring(L, str.data(), str.length());
}
