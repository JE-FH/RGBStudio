#pragma once
#include "ILuaValue.hpp"
#include "lua.hpp"
class LuaIntegerValue :
    public ILuaValue
{
public:
    LuaIntegerValue(lua_Integer integer);

    lua_Integer integer;
    // Inherited via ILuaValue
    virtual void push_value(lua_State* L) override;
};

