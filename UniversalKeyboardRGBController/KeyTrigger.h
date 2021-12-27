#pragma once
#include "Trigger.h"
class KeyTrigger
	: public Trigger
{
public:
	KeyTrigger(unsigned short trigger_key);

	// Inherited via Trigger
	virtual void handle_event(EffectManager& effect_manager, Event& ev) override;
private:
	unsigned short _trigger_key;
};

