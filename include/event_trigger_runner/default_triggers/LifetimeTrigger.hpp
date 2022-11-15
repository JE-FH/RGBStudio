#pragma once
#include "../Trigger.hpp"

class LifetimeTrigger : public Trigger {
public:
	LifetimeTrigger(std::string trigger_name);

	virtual bool should_trigger(Event& ev, std::string& trigger_sub_name) override;
private:
};
