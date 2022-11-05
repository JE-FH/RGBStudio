#pragma once
#include "../Trigger.hpp"
class KeyTrigger
	: public Trigger
{
public:
	KeyTrigger(std::string trigger_name, unsigned short trigger_key, bool trigger_on_first_press, bool trigger_on_release, bool trigger_on_repeat);

	// Inherited via Trigger
	virtual bool should_trigger(Event& ev) override;
private:
	unsigned short _trigger_key;
	bool _trigger_on_press;
	bool _trigger_on_release;
	bool _trigger_on_repeat;
};

