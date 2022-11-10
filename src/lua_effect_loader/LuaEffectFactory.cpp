#include <lua_effect_loader/LuaEffectFactory.hpp>
#include <lua_effect_loader/LuaUtils.hpp>
#include <lua.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>
#include <lua_effect_loader/LuaEffect.hpp>

std::unique_ptr<IConfigValueTypeDesc> HintToType(std::string hint) {
	if (hint == ConfigStringTypeDesc::friendly_name()) {
		return std::make_unique<ConfigStringTypeDesc>();
	}
	else if (hint == ConfigIntegerTypeDesc::friendly_name()) {
		return std::make_unique<ConfigIntegerTypeDesc>();
	}
	else if (hint == ConfigNumberTypeDesc::friendly_name()) {
		return std::make_unique<ConfigNumberTypeDesc>();
	}
	else if (hint == ConfigRGBColorTypeDesc::friendly_name()) {
		return std::make_unique<ConfigRGBColorTypeDesc>();
	}
	else if (hint == ConfigBoolTypeDesc::friendly_name()) {
		return std::make_unique<ConfigBoolTypeDesc>();
	}
	else if (hint == ConfigActionNameTypeDesc::friendly_name()) {
		return std::make_unique<ConfigActionNameTypeDesc>();
	}
	return nullptr;
}

LuaEffectFactory::LuaEffectFactory(std::string _file_name)
{
	file_name = std::move(_file_name);
	LuaStatePtr L(luaL_newstate());

	luaL_openlibs(L);
	if (luaL_dofile(L, file_name.c_str()) != 0) {
		throw std::runtime_error("Lua error " + std::string(lua_tostring(L, -1)));
	}

	if (lua_getglobal(L, "define") != LUA_TFUNCTION) {
		throw std::runtime_error(file_name + "has no define function");
	}

	if (lua_pcall(L, 0, 1, 0) != 0) {
		throw std::runtime_error("Lua error: " + std::string(lua_tostring(L, -1)));
	}

	if (!lua_istable(L, -1)) {
		throw std::runtime_error(file_name + " define needs to return a table");
	}

	lua_pushstring(L, "properties");
	lua_rawget(L, -2);
	if (!lua_istable(L, -1)) {
		throw std::runtime_error(file_name + " properties in definition needs to be a table");
	}

	lua_pushnil(L);
	while (lua_next(L, -2)) {
		lua_pushvalue(L, -2);

		const char* key = lua_tostring(L, -1);
		std::unique_ptr<IConfigValueTypeDesc> typeDesc;
		if (lua_isstring(L, -2)) {
			const char* value = lua_tostring(L, -2);
			typeDesc = HintToType(value);
			if (typeDesc == nullptr) {
				throw std::runtime_error(file_name + " properties specification got unknown hint \"" + value + "\"");
			}
		}
		else 
		{
			throw std::runtime_error(file_name + " settings specification needs to be a table with string key and string value");
		}
		
		config_spec.add_field(key, std::move(typeDesc), true);
		lua_pop(L, 2);
	}
	lua_pop(L, 1);

	lua_pushstring(L, "name");
	lua_rawget(L, -2);
	const char* key = lua_tostring(L, -1);
	given_name = std::string(key);
}

std::unique_ptr<IEffect> LuaEffectFactory::create(const DynamicConfig& dynamic_config, std::shared_ptr<IKeyboardDevice> device)
{
	//TODO: move layer somewhere else or let lua decide it
	auto effect_settings = LuaEffectSettings::from_dynamic_config(dynamic_config, config_spec);
	return std::make_unique<LuaEffect>(0, std::move(device), file_name, effect_settings);
}

const DynamicConfigSpec& LuaEffectFactory::get_config_spec() const
{
	return config_spec;
}

std::string LuaEffectFactory::get_name() const
{
	return given_name;
}
