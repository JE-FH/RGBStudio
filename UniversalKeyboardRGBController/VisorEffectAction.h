#pragma once
#include "IEffectAction.h"
class VisorEffectAction :
    public IEffectAction
{
public:
    VisorEffectAction(double speed, RGBColor color);
    // Inherited via IEffectAction
    virtual void do_effect(EffectManager& effectManager) override;
private:
    double _speed;
    RGBColor _color;
};

