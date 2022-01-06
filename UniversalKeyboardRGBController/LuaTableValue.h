#pragma once
#include "ILuaValue.h"
#include <string>
#include <map>
#include <memory>
class LuaTableValue :
    public ILuaValue
{
public:
    std::map<std::string, std::unique_ptr<ILuaValue>> table;

    // Inherited via ILuaValue
    virtual void push_value(lua_State* L) override;
};

