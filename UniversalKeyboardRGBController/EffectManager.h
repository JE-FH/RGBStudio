#pragma once
#include "Effect.h"
#include "IKeyboardDevice.h"
#include <vector>
#include <memory>
#include <chrono>
class EffectManager
{
public:
	EffectManager(std::unique_ptr<IKeyboardDevice> device);

	void add_effect(std::unique_ptr<Effect> effect);
	void tick();
private:
	std::vector<std::unique_ptr<Effect>> _effects;
	std::unique_ptr<IKeyboardDevice> _device;
	std::chrono::system_clock::time_point _last_tick;
};

