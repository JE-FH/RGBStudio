#pragma once
#include "ILuaValue.h"
#include <lua.hpp>
#include <string>

class LuaStringValue :
    public ILuaValue
{
public:
    LuaStringValue(std::string str);

    std::string str;

    // Inherited via ILuaValue
    virtual void push_value(lua_State* L) override;
};
