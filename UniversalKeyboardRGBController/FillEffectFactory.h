#pragma once
#include "IEffectFactory.h"
#include "RGBColor.h"
#include <string>
class FillEffectFactory :
    public IEffectFactory
{
public:
    FillEffectFactory(int layer, std::string stop_trigger, RGBColor color);

    // Inherited via IEffectFactory
    virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) override;
    
private:
    int _layer;
    std::string _stop_trigger;
    RGBColor _color;
};

