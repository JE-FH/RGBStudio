#pragma once
#include "EffectManager.h"
class IEffectAction {
public:
	virtual ~IEffectAction() {}
	virtual void do_effect(EffectManager& effect_manager) = 0;

};