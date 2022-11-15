#pragma once
#include "../Trigger.hpp"
class KeyTrigger
	: public Trigger
{
public:
	KeyTrigger(std::string trigger_name, int trigger_key);

	// Inherited via Trigger
	virtual bool should_trigger(Event& ev, std::string& trigger_sub_name) override;
private:
	int _trigger_key;
};

