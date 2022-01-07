#pragma once
#include "IEffectFactory.h"
#include "LuaEffectSettings.h"
#include "LuaUtils.h"
#include "LuaIKeyboardDeviceAdapter.h"
#include <lua.hpp>
class LuaEffectFactory :
    public IEffectFactory
{
public:
    LuaEffectFactory(const LuaEffectFactory&) = delete;
    LuaEffectFactory(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, const std::string& file_name, LuaEffectSettings& settings);
    ~LuaEffectFactory();
    
    // Inherited via IEffectFactory
    virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) override;
private:
    LuaStatePtr L;
    std::shared_ptr<IKeyboardDevice> _keyboard_device;
    LuaIKeyboardDeviceAdapter _keyboard_device_adapter;

    int _layer;
};

