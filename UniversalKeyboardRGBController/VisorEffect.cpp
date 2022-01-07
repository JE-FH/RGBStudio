#include "VisorEffect.h"
#include <iostream>

VisorEffect::VisorEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, const double speed, RGBColor color)
	: Effect(layer, keyboard_device)
{
	_begin_time = std::chrono::system_clock::now();
	_speed = speed;
	_color = std::move(color);
 	_keyboard_device = std::move(keyboard_device);
}

void VisorEffect::draw(double delta)
{
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<float> spawn_delta = now - _begin_time;
	double fill_length = spawn_delta.count() * _speed;
	for (auto it = _keyboard_device->key_begin(); it != _keyboard_device->key_end(); it++) {
		if (fill_length + 1 > (*it)->x && fill_length - 1 < (*it)->x) {
			(*it)->set_color(_color, 1);
		}
	}
	
	if (fill_length > _keyboard_device->get_width()) {
		mark_completed();
	}
}
