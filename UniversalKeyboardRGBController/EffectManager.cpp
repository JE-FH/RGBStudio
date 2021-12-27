#include "EffectManager.h"
#include <iostream>
EffectManager::EffectManager(std::unique_ptr<IKeyboardDevice> device)
{
	_device = std::move(device);
	_last_tick = std::chrono::system_clock::now();
}

void EffectManager::add_effect(std::unique_ptr<Effect> effect)
{
	_effects.push_back(std::move(effect));
}

void EffectManager::tick()
{
	auto now = std::chrono::system_clock::now();
	float delta = ((std::chrono::duration<float>) (now - _last_tick)).count();
	
	_device->fill(RGBColor{0, 0, 0});
	
	for (auto& effect : _effects) {
		effect->draw(_device.get(), delta);
	}
	_last_tick = now;
	for (int i = _effects.size() - 1; i >= 0; i--) {
		if (_effects[i]->is_completed()) {
			_effects.erase(_effects.begin() + i);
		}
	}
	_device->apply_colors();
}
