#pragma once
#include <effect_manager/EffectInstance.hpp>
#include <event_trigger_runner/TriggerObserverDispatcher.hpp>
#include "LuaEffectSettings.hpp"
#include "LuaUtils.hpp"
#include "LuaIKeyboardDeviceAdapter.hpp"
#include "LuaTriggerObserverDispatcherAdapter.hpp"
#include <lua.hpp>
class LuaEffectInstance :
    public EffectInstance
{
public:
    LuaEffectInstance(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, TriggerObserverDispatcher& trigger_observer_dispatcher, LuaStatePtr thread);
    LuaEffectInstance(const LuaEffectInstance&) = delete;
    ~LuaEffectInstance();
    // Inherited via Effect
    virtual void draw(double delta) override;
private:
    LuaStatePtr L;
    LuaTriggerObserverDispatcherAdapter dispatcher;
    int _state_ref;
};

