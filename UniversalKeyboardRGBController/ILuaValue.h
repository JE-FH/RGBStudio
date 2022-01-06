#pragma once
#include <lua.hpp>
class ILuaValue {
public:
	virtual ~ILuaValue() {}
	virtual void push_value(lua_State* L) = 0;
};