#pragma once
#include "EffectManager.h"
#include "TriggerObserverDispatcher.h"
class IEffectFactory {
public:
	virtual ~IEffectFactory() {}
	virtual void add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher) = 0;
};