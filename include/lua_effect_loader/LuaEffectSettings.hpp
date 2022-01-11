#pragma once
#include "LuaTableValue.hpp"
#include "ILuaValue.hpp"
#include <string>

class LuaEffectSettings
{
public:
	void set_setting(std::string index, std::unique_ptr<ILuaValue> value);
	void unset_setting(const std::string& index);
	void push_value(lua_State* L);
private:
	LuaTableValue lua_table_value;
};

