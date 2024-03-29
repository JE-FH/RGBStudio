#pragma once
#include <effect_manager/EffectManager.hpp>
#include "TriggerObserverDispatcher.hpp"
class IEffect {
public:
	virtual ~IEffect() {}
	virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) = 0;
};