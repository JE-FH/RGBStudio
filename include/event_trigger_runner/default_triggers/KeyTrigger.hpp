#pragma once
#include "../Trigger.hpp"
class KeyTrigger
	: public Trigger
{
public:
	KeyTrigger(std::string trigger_name, unsigned short trigger_key);

	// Inherited via Trigger
	virtual bool should_trigger(Event& ev, std::string& trigger_sub_name) override;
private:
	unsigned short _trigger_key;
};

