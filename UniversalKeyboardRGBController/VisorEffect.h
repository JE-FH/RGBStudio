#pragma once
#include "Effect.h"
#include <chrono>
class VisorEffect :
    public Effect
{
public:
    VisorEffect(const double speed, const RGBColor& color);
    // Inherited via IEffect
    virtual void draw(IKeyboardDevice* device, double delta) override;
private:
    std::chrono::system_clock::time_point _begin_time;
    double _speed;
    RGBColor _color;
};

