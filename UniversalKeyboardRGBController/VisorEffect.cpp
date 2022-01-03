#include "VisorEffect.h"
#include <iostream>

VisorEffect::VisorEffect(int layer, const double speed, RGBColor color)
	: Effect(layer)
{
	_begin_time = std::chrono::system_clock::now();
	_speed = speed;
	_color = std::move(color);
}

void VisorEffect::draw(IKeyboardDevice* device, double delta)
{
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<float> spawn_delta = now - _begin_time;
	double fill_length = spawn_delta.count() * _speed;
	for (auto it = device->key_begin(); it != device->key_end(); it++) {
		if (fill_length + 1 > (*it)->x && fill_length - 1 < (*it)->x) {
			(*it)->layer_color(_color, 0.5);
		}
	}
	
	if (fill_length > device->get_width()) {
		mark_completed();
	}
}
