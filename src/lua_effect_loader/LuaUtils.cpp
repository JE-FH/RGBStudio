#include <lua_effect_loader/LuaUtils.hpp>

std::string lua_tostdstring(lua_State* L, int idx) {
	size_t len;
	const char* data = lua_tolstring(L, idx, &len);

	return std::string(data, len);
}
