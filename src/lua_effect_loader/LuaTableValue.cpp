#include <lua_effect_loader/LuaTableValue.hpp>

void LuaTableValue::push_value(lua_State* L)
{
	lua_createtable(L, 0, table.size());

	for (auto& element : table) {
		lua_pushlstring(L, element.first.data(), element.first.size());
		element.second->push_value(L);
		lua_settable(L, -3);
	}
}
