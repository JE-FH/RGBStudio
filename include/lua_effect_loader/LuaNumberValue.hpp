#pragma once
#include "ILuaValue.hpp"
#include <lua.hpp>
class LuaNumberValue :
    public ILuaValue
{
public:
    LuaNumberValue(LUA_NUMBER number);

    LUA_NUMBER number;
    
    // Inherited via ILuaValue
    virtual void push_value(lua_State* L) override;
};
