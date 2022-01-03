#include "FlashEffect.h"

FlashEffect::FlashEffect(int layer, const double rising_duration, const double sustain_duration, const double falling_duration, RGBColor color)
	: Effect(layer)
{
	this->rising_duration = rising_duration;
	this->sustain_duration = sustain_duration;
	this->falling_duration = falling_duration;
	this->color = std::move(color);

}

void FlashEffect::draw(IKeyboardDevice* device, double delta)
{
}
