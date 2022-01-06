#pragma once
#include "Effect.h"
#include "TriggerObserverDispatcher.h"
#include "LuaEffectSettings.h"
#include "LuaUtils.h"
#include <lua.hpp>
class LuaEffect :
    public Effect, private TriggerObserver
{
public:
    LuaEffect(int layer, TriggerObserverDispatcher& trigger_observer_dispatcher, LuaStatePtr thread);
    LuaEffect(const LuaEffect&) = delete;
    ~LuaEffect();
    // Inherited via Effect
    virtual void draw(IKeyboardDevice* device, double delta) override;
private:
    LuaStatePtr L;
    int _state_ref;

    // Inherited via TriggerObserver
    virtual void Trigger(std::string trigger_name) override;
};

