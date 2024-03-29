#pragma once
#include <effect_manager/EffectInstance.hpp>
#include <chrono>
class VisorEffectInstance :
    public EffectInstance
{
public:
    VisorEffectInstance(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, const double speed, RGBColor color);
    // Inherited via IEffect
    virtual void draw(double delta) override;
private:
    std::chrono::system_clock::time_point _begin_time;
    double _speed;
    RGBColor _color;
};

