#pragma once
#include "EffectInstance.hpp"
#include <device_adapter_loader/IKeyboardDevice.hpp>
#include <vector>
#include <memory>
#include <chrono>
class EffectManager
{
public:
	EffectManager();

	void add_device(std::shared_ptr<IKeyboardDevice> _device);
	void add_effect_instance(std::unique_ptr<EffectInstance> effect);
	void tick();
	void clear();
private:
	std::vector<std::unique_ptr<EffectInstance>> _effects;
	std::vector<std::shared_ptr<IKeyboardDevice>> _devices;
	std::chrono::system_clock::time_point _last_tick;
};

