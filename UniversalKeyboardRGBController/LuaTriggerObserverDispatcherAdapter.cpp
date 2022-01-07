#include "LuaTriggerObserverDispatcherAdapter.h"

const char* LuaTriggerObserverDispatcherAdapter::meta_table_name = "UniversalKeyboardRGBController.LuaTriggerObserverDispatcherAdapater";
const luaL_Reg LuaTriggerObserverDispatcherAdapter::arraylib_m[] = {
	{"add_trigger", LuaTriggerObserverDispatcherAdapter::lib_add_trigger},
	{NULL, NULL}
};

LuaTriggerObserverDispatcherAdapter::LuaTriggerObserverDispatcherAdapter(TriggerObserverDispatcher& trigger_observer_dispatcher, lua_State* L, int state_ref)
{
	_trigger_observer_dispatcher = &trigger_observer_dispatcher;
	this->L = L;
	_state_ref = state_ref;
}

LuaTriggerObserverDispatcherAdapter::~LuaTriggerObserverDispatcherAdapter()
{
	for (auto& callback : callback_refs) {
		luaL_unref(L, LUA_REGISTRYINDEX, callback.second);
	}
}

void LuaTriggerObserverDispatcherAdapter::push_object()
{
	lua_newuserdata(L, sizeof(LuaTriggerObserverDispatcherAdapter*));
	luaL_getmetatable(L, meta_table_name);
	lua_setmetatable(L, -2);

	LuaTriggerObserverDispatcherAdapter** ud = (LuaTriggerObserverDispatcherAdapter**)luaL_checkudata(L, -1, meta_table_name);
	*ud = this;
}

void LuaTriggerObserverDispatcherAdapter::openlib(LuaStatePtr& L)
{
	luaL_newmetatable(L, meta_table_name);
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, arraylib_m, 0);
	lua_pop(L, 1);
}

void LuaTriggerObserverDispatcherAdapter::add_trigger(const std::string& trigger, lua_Integer ref)
{
	callback_refs.insert(std::pair(trigger, ref));
	auto range = callback_refs.equal_range(trigger);
	if (callback_refs.count(trigger) == 1) {
		_trigger_observer_dispatcher->add_observer(trigger, *this);
	}
}

LuaTriggerObserverDispatcherAdapter* LuaTriggerObserverDispatcherAdapter::check_metatable(lua_State* L)
{
	LuaTriggerObserverDispatcherAdapter** ud = (LuaTriggerObserverDispatcherAdapter**)luaL_checkudata(L, 1, meta_table_name);
	luaL_argcheck(L, ud != nullptr, 1, "TriggerObserverDispatcher expected");
	luaL_argcheck(L, *ud != nullptr, 1, "TriggerObserverDispatcher has been invalidated (cannot be used after init_instance call returned)");

	return *ud;
}

void LuaTriggerObserverDispatcherAdapter::Trigger(const std::string& trigger_name)
{
	auto range = callback_refs.equal_range(trigger_name);
	for (auto it = range.first; it != range.second; it++) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, it->second);
		lua_pushlstring(L, trigger_name.data(), trigger_name.size());
		lua_rawgeti(L, LUA_REGISTRYINDEX, _state_ref);

		if (lua_pcall(L, 2, 0, 0) != 0) {
			printf("Lua error on trigger: %s\n", lua_tostring(L, -1));
		}
	}
}

int LuaTriggerObserverDispatcherAdapter::lib_add_trigger(lua_State* L)
{
	auto _this = check_metatable(L);

	luaL_argcheck(L, lua_isstring(L, 2), 2, "Second argument has to be a string");
	luaL_argcheck(L, lua_isfunction(L, 3), 3, "Third argument has to be a callback function");
	lua_pushvalue(L, 3);
	
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	auto trigger_name = lua_tostdstring(L, 2);

	_this->add_trigger(trigger_name, ref);

	return 0;
}