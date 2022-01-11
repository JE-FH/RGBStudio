#pragma once
#include <event_trigger_runner/IEffectFactory.hpp>
#include <effect_manager/RGBColor.hpp>
#include <effect_manager/IKeyboardDevice.hpp>
#include <string>
class FillEffectFactory :
    public IEffectFactory
{
public:
    FillEffectFactory(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, std::string stop_trigger, RGBColor color);

    // Inherited via IEffectFactory
    virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) override;
    
private:
    int _layer;
    std::string _stop_trigger;
    RGBColor _color;
    std::shared_ptr<IKeyboardDevice> _keyboard_device;
};

