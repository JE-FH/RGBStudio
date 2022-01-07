#include "LuaEffect.h"

LuaEffect::LuaEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, TriggerObserverDispatcher& trigger_observer_dispatcher, LuaStatePtr thread)
	: Effect(layer, std::move(keyboard_device)),
	L(std::move(thread)),
	dispatcher(trigger_observer_dispatcher, L, 0)
{
	lua_createtable(L, 0, 0);
	_state_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	dispatcher._state_ref = _state_ref;

	if (lua_getglobal(L, "init_instance") != LUA_TFUNCTION) {
		printf("No init_instance function\n");
		return;
	}

	lua_rawgeti(L, LUA_REGISTRYINDEX, _state_ref);
	dispatcher.push_object();

	if (lua_pcall(L, 2, 0, 0) != 0) {
		printf("Lua error: %s\n", lua_tostring(L, -1));
		mark_completed();
	}
}

LuaEffect::~LuaEffect()
{
	if (L != nullptr) {
		luaL_unref(L, LUA_REGISTRYINDEX, _state_ref);
	}
}

void LuaEffect::draw(double delta)
{
	if (lua_getglobal(L, "draw") != LUA_TFUNCTION) {
		printf("No draw function\n");
		mark_completed();
		return;
	}

	

	lua_rawgeti(L, LUA_REGISTRYINDEX, _state_ref);
	lua_pushnumber(L, delta);

	auto res = lua_pcall(L, 2, 0, 0);
	if (res != 0) {
		printf("Lua error :%s\n", lua_tostring(L, -1));
		mark_completed();
		return;
	}

	lua_rawgeti(L, LUA_REGISTRYINDEX, _state_ref);
	lua_pushstring(L, "completed");
	if (lua_gettable(L, -2) == LUA_TBOOLEAN) {
		if (lua_toboolean(L, -1)) {
			mark_completed();
		}
	}
	lua_pop(L, 2);
}