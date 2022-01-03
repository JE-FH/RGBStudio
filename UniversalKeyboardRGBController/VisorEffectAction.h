#pragma once
#include "IEffectFactory.h"
class VisorEffectAction :
    public IEffectFactory
{
public:
    VisorEffectAction(double speed, RGBColor color);

    // Inherited via IEffectFactory
    virtual void add_new_instance(EffectManager& effect_manager) override;
private:
    double _speed;
    RGBColor _color;
};

