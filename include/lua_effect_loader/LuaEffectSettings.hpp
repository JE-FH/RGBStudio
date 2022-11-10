#pragma once
#include "LuaTableValue.hpp"
#include "ILuaValue.hpp"
#include <string>
#include <dynamic_config/DynamicConfigSpec.hpp>
#include <dynamic_config/DynamicConfig.hpp>

class LuaEffectSettings
{
public:
	void set_setting(std::string index, std::unique_ptr<ILuaValue> value);
	void unset_setting(const std::string& index);
	void push_value(lua_State* L);
	static LuaEffectSettings from_dynamic_config(const DynamicConfig& config, const DynamicConfigSpec& spec);
private:
	LuaTableValue lua_table_value;
};

