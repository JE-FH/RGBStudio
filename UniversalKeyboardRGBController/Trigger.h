#pragma once
#include "Event.h"
#include <vector>
class Trigger {
public:
	Trigger(std::string trigger_name) : trigger_name(std::move(trigger_name)) {}
	virtual ~Trigger() {}
	virtual bool should_trigger(Event& ev) = 0;
	
	const std::string trigger_name;
};