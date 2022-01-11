#include <lua_effect_loader/LuaIntegerValue.hpp>

LuaIntegerValue::LuaIntegerValue(lua_Integer integer) {
    this->integer = integer;
}

void LuaIntegerValue::push_value(lua_State* L)
{
    lua_pushinteger(L, integer);
}
