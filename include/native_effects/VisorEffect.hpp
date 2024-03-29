#pragma once
#include <event_trigger_runner/IEffect.hpp>
#include <event_trigger_runner/TriggerObserverDispatcher.hpp>
#include <device_adapter_loader/IKeyboardDevice.hpp>

class VisorEffect :
    public IEffect
{
public:
    VisorEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, double speed, RGBColor color);

    // Inherited via IEffectFactory
    virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) override;
private:
    double _speed;
    RGBColor _color;
    int _layer;
    std::shared_ptr<IKeyboardDevice> _keyboard_device;
};

