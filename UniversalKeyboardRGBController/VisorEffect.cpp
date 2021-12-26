#include "VisorEffect.h"
#include <iostream>

VisorEffect::VisorEffect(const double speed, const RGBColor& color)
{
	_begin_time = std::chrono::system_clock::now();
	_speed = speed;
	_color = color;
}

void VisorEffect::draw(IKeyboardDevice* device, double delta)
{
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<float> spawn_delta = now - _begin_time;
	double fill_length = spawn_delta.count() * _speed;
	for (auto it = device->key_begin(); it != device->key_end(); it++) {
		if (fill_length + 2 > (*it)->x && fill_length < (*it)->x) {
			(*it)->set_color(_color);
		}
	}
	
	if (fill_length > device->get_width()) {
		mark_completed();
	}
}
