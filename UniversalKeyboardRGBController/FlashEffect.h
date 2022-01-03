#pragma once
#include "Effect.h"
#include "RGBColor.h"
#include <chrono>

class FlashEffect
	: Effect
{
public:
	FlashEffect(int layer, const double rising_duration, const double sustain_duration, const double falling_duration, RGBColor color);
	// Inherited via IEffect
	virtual void draw(IKeyboardDevice* device, double delta) override;
private:
	std::chrono::system_clock::time_point _begin_time;
	double rising_duration;
	double sustain_duration;
	double falling_duration;
	RGBColor color;
};

