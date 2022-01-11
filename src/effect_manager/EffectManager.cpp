#include <effect_manager/EffectManager.hpp>
#include <iostream>
#include <algorithm>

EffectManager::EffectManager()
{
	_last_tick = std::chrono::system_clock::now();
}

void EffectManager::add_device(std::shared_ptr<IKeyboardDevice> _device)
{
	_devices.push_back(std::move(_device));
}

void EffectManager::add_effect(std::unique_ptr<Effect> effect)
{
	_effects.push_back(std::move(effect));
	std::sort(_effects.begin(), _effects.end(), [](std::unique_ptr<Effect>& a, std::unique_ptr<Effect>& b) {
		return a->layer < b->layer;
	});
}

void EffectManager::tick()
{
	auto now = std::chrono::system_clock::now();
	float delta = ((std::chrono::duration<float>) (now - _last_tick)).count();
	
	for (auto& device : _devices) {
		device->fill(RGBColor{0, 0, 0});
	}
	
	for (auto& effect : _effects) {
		effect->draw(delta);
	}
	_last_tick = now;
	for (int i = _effects.size() - 1; i >= 0; i--) {
		if (_effects[i]->is_completed()) {
			_effects.erase(_effects.begin() + i);
		}
	}

	for (auto& device : _devices) {
		device->apply_colors();
	}
}
