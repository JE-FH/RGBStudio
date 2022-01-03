#pragma once
#include "EffectManager.h"
class IEffectFactory {
public:
	virtual ~IEffectFactory() {}
	virtual void add_new_instance(EffectManager& effect_manager) = 0;
};