#include "LuaEffectFactory.h"
#include "LuaEffect.h"
#include "LuaIKeyboardDeviceAdapter.h"

LuaEffectFactory::LuaEffectFactory(int layer, const std::string& file_name, LuaEffectSettings& settings)
	: L(luaL_newstate())
{
	_layer = layer;

	luaL_openlibs(L);
	LuaIKeyboardDeviceAdapter::openlib(L);

	if (luaL_dofile(L, file_name.c_str()) != 0) {
		throw std::runtime_error("Lua error " + std::string(lua_tostring(L, -1)));
	}

	if (lua_getglobal(L, "init") != LUA_TFUNCTION) {
		throw std::runtime_error(file_name + "has no init function");
	}

	settings.push_value(L);

	if (lua_pcall(L, 1, 0, 0) != 0) {
		throw std::runtime_error("Lua error: " + std::string(lua_tostring(L, -1)));
	}
}

LuaEffectFactory::~LuaEffectFactory()
{
	if (L != nullptr) {
		lua_close(L);
	}
}

void LuaEffectFactory::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect(std::make_unique<LuaEffect>(_layer, trigger_observer_dispatcher, LuaStatePtr(lua_newthread(L), true)));
}
