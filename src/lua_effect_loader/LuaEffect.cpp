#include <lua_effect_loader/LuaEffect.hpp>
#include <lua_effect_loader/LuaEffectInstance.hpp>
#include <lua_effect_loader/LuaIKeyboardDeviceAdapter.hpp>

LuaEffect::LuaEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, const std::string& file_name, LuaEffectSettings& settings)
	: L(luaL_newstate()), _keyboard_device_adapter(keyboard_device)
{
	_keyboard_device = std::move(keyboard_device);
	_layer = layer;

	luaL_openlibs(L);
	LuaIKeyboardDeviceAdapter::openlib(L);
	LuaTriggerObserverDispatcherAdapter::openlib(L);

	if (luaL_dofile(L, file_name.c_str()) != 0) {
		throw std::runtime_error("Lua error " + std::string(lua_tostring(L, -1)));
	}

	if (lua_getglobal(L, "init") != LUA_TFUNCTION) {
		throw std::runtime_error(file_name + "has no init function");
	}

	settings.push_value(L);
	_keyboard_device_adapter.push_device(L);

	if (lua_pcall(L, 2, 0, 0) != 0) {
		throw std::runtime_error("Lua error: " + std::string(lua_tostring(L, -1)));
	}
}

LuaEffect::~LuaEffect()
{
	if (L != nullptr) {
		lua_close(L);
	}
}

void LuaEffect::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect_instance(std::make_unique<LuaEffectInstance>(_layer, _keyboard_device, trigger_observer_dispatcher, L.new_thread()));
}
