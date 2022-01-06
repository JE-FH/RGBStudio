#pragma once
#include "IEffectFactory.h"
#include "LuaEffectSettings.h"
#include "LuaUtils.h"
#include <lua.hpp>
class LuaEffectFactory :
    public IEffectFactory
{
public:
    LuaEffectFactory(const LuaEffectFactory&) = delete;
    LuaEffectFactory(int layer, const std::string& file_name, LuaEffectSettings& settings);
    ~LuaEffectFactory();
    
    // Inherited via IEffectFactory
    virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) override;
private:
    LuaStatePtr L;
    int _layer;
};

