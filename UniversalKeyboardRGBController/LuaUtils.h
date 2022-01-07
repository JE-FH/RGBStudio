#pragma once
#include <lua.hpp>
#include <string>
class LuaStatePtr {
public:
	LuaStatePtr(lua_State* L, bool is_thread = false) {
		this->L = L;
		_is_thread = is_thread;
	}

	LuaStatePtr(const LuaStatePtr& other) = delete;

	LuaStatePtr(LuaStatePtr&& other) noexcept {
		L = other.L;
		other.L = nullptr;
		_is_thread = other._is_thread;
	}

	~LuaStatePtr() {
		if (L != nullptr && !_is_thread) {
			lua_close(L);
		}
	}

	operator lua_State* () const {
		return L;
	}
private:
	lua_State* L;
	bool _is_thread;
};

std::string lua_tostdstring(lua_State* L, int idx);
