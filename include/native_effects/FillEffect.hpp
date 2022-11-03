#pragma once
#include <event_trigger_runner/IEffect.hpp>
#include <device_adapter_loader/RGBColor.hpp>
#include <device_adapter_loader/IKeyboardDevice.hpp>
#include <string>
class FillEffect :
    public IEffect
{
public:
    FillEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, std::string stop_trigger, RGBColor color);

    // Inherited via IEffectFactory
    virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) override;
    
private:
    int _layer;
    std::string _stop_trigger;
    RGBColor _color;
    std::shared_ptr<IKeyboardDevice> _keyboard_device;
};

