#pragma once
#include "TriggerObserverDispatcher.h"
#include "TriggerObserver.h"
#include "lua.hpp"
#include "LuaUtils.h"
#include <map>

class LuaTriggerObserverDispatcherAdapter
	: private TriggerObserver
{
public:
	LuaTriggerObserverDispatcherAdapter(const LuaTriggerObserverDispatcherAdapter&) = delete;
	LuaTriggerObserverDispatcherAdapter(LuaTriggerObserverDispatcherAdapter&&) = delete;
	LuaTriggerObserverDispatcherAdapter(TriggerObserverDispatcher& trigger_observer_dispatcher, lua_State* L, int state_ref);
	~LuaTriggerObserverDispatcherAdapter();
	void push_object();

	static void openlib(LuaStatePtr& L);

	// Inherited via TriggerObserver
	virtual void Trigger(const std::string& trigger_name) override;
	
	int _state_ref;
private:
	TriggerObserverDispatcher* _trigger_observer_dispatcher;
	lua_State* L;

	//Map from action to callback ref
	std::multimap<std::string, lua_Integer> callback_refs;

	void add_trigger(const std::string& trigger, lua_Integer ref);

	static const char* meta_table_name;
	static const luaL_Reg arraylib_m[];

	static LuaTriggerObserverDispatcherAdapter* check_metatable(lua_State* L);

	static int lib_add_trigger(lua_State* L);
};

