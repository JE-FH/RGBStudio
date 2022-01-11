#pragma once
#include <lua.hpp>
#include <string>
#include <memory>

class LuaStatePtr {
public:
	LuaStatePtr(lua_State* L) {
		this->L = L;
		_thread_ref = -1;
		_thread = L;
		_L_ref_count = std::make_shared<size_t>();
		*_L_ref_count = 1;
	}

	LuaStatePtr(const LuaStatePtr& other) = delete;

	LuaStatePtr(LuaStatePtr&& other) noexcept {
		L = other.L;
		other.L = nullptr;
		
		_thread = other._thread;
		other._thread = nullptr;

		_thread_ref = other._thread_ref;

		_L_ref_count = std::move(other._L_ref_count);
	}

	~LuaStatePtr() {
		//This object has been moved so we dont do anything
		if (_L_ref_count == nullptr) {
			return;
		}
		*_L_ref_count -= 1;
		if (*_L_ref_count == 0) {
			lua_close(L);
		} else {
			if (_thread_ref != -1) {
				luaL_unref(L, LUA_REGISTRYINDEX, _thread_ref);
			}
		}
	}

	operator lua_State* () const {
		return _thread;
	}

	LuaStatePtr new_thread() {
		lua_State* new_thread = lua_newthread(L);
		int new_thread_ref = luaL_ref(L, LUA_REGISTRYINDEX);
		return LuaStatePtr(L, new_thread, new_thread_ref, _L_ref_count);
	}
private:
	LuaStatePtr(lua_State* L, lua_State* thread, int thread_ref, std::shared_ptr<size_t> L_ref_count) {
		this->L = L;
		_thread = thread;
		_L_ref_count = std::move(L_ref_count);
		*_L_ref_count += 1;
		_thread_ref = thread_ref;
	}

	lua_State* L;
	lua_State* _thread;
	std::shared_ptr<size_t> _L_ref_count;
	int _thread_ref;
};

std::string lua_tostdstring(lua_State* L, int idx);
