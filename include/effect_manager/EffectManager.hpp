#pragma once
#include "Effect.hpp"
#include "IKeyboardDevice.hpp"
#include <vector>
#include <memory>
#include <chrono>
class EffectManager
{
public:
	EffectManager();

	void add_device(std::shared_ptr<IKeyboardDevice> _device);
	void add_effect(std::unique_ptr<Effect> effect);
	void tick();
private:
	std::vector<std::unique_ptr<Effect>> _effects;
	std::vector<std::shared_ptr<IKeyboardDevice>> _devices;
	std::chrono::system_clock::time_point _last_tick;
};

