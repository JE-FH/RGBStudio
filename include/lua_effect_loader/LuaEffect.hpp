#pragma once
#include <event_trigger_runner/IEffect.hpp>
#include "LuaEffectSettings.hpp"
#include "LuaUtils.hpp"
#include "LuaIKeyboardDeviceAdapter.hpp"
#include <lua.hpp>
#include <dynamic_config/DynamicConfigSpec.hpp>
class LuaEffect :
    public IEffect
{
public:
    LuaEffect(const LuaEffect&) = delete;
    //TODO: LuaEffectSettings can be marked const here
    LuaEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, const std::string& file_name, LuaEffectSettings& settings);
    ~LuaEffect();
    
    // Inherited via IEffect
    virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) override;
private:
    LuaStatePtr L;
    std::shared_ptr<IKeyboardDevice> _keyboard_device;
    LuaIKeyboardDeviceAdapter _keyboard_device_adapter;

    int _layer;
};

