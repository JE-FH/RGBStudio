#include <lua_effect_loader/LuaEffectSettings.hpp>
#include <dynamic_config/DynamicConfig.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>
#include <lua_effect_loader/LuaStringValue.hpp>
#include <lua_effect_loader/LuaIntegerValue.hpp>
#include <lua_effect_loader/LuaNumberValue.hpp>

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

std::unique_ptr<ILuaValue> DynamicConfigValueToLuaValue(const IConfigValue& value) {
	if (auto strValue = dynamic_cast<const ConfigStringValue*>(&value)) {
		return std::make_unique<LuaStringValue>(strValue->get_value());
	} else if (auto intValue = dynamic_cast<const ConfigIntegerValue*>(&value)) {
		return std::make_unique<LuaIntegerValue>(intValue->get_value());
	} else if (auto numberValue = dynamic_cast<const ConfigNumberValue*>(&value)) {
		return std::make_unique<LuaNumberValue>(numberValue->get_value());
	} else if (auto rgbColorValue = dynamic_cast<const ConfigRGBColorValue*>(&value)) {
		auto table = std::make_unique<LuaTableValue>();
		
		table->table.insert(std::pair("r", std::make_unique<LuaIntegerValue>(rgbColorValue->get_value().r)));
		table->table.insert(std::pair("g", std::make_unique<LuaIntegerValue>(rgbColorValue->get_value().g)));
		table->table.insert(std::pair("b", std::make_unique<LuaIntegerValue>(rgbColorValue->get_value().b)));
		
		return table;
	} else if (auto boolValue = dynamic_cast<const ConfigBoolTypeDesc*>(&value)) {
		//TODO: Implement this
		return nullptr;
	} else if (auto actionName = dynamic_cast<const ConfigActionNameValue*>(&value)) {
		return std::make_unique<LuaStringValue>(actionName->get_value());
	}
}

LuaEffectSettings LuaEffectSettings::from_dynamic_config(const DynamicConfig& config, const DynamicConfigSpec& spec) {
	LuaEffectSettings lua_effect_settings;
	const auto& fields = spec.get_fields();
	for (const auto& field : fields) {
		lua_effect_settings.set_setting(
			field.name, 
			DynamicConfigValueToLuaValue(*config.get_config_value(field.name))
		);
	}
	return lua_effect_settings;
}