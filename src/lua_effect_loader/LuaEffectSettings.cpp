#include <lua_effect_loader/LuaEffectSettings.hpp>

void LuaEffectSettings::set_setting(std::string index, std::unique_ptr<ILuaValue> value)
{
	lua_table_value.table.insert(std::pair(std::move(index), std::move(value)));
}

void LuaEffectSettings::unset_setting(const std::string& index)
{
	lua_table_value.table.erase(index);
}

void LuaEffectSettings::push_value(lua_State* L)
{
	lua_table_value.push_value(L);
}
