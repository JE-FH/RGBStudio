#pragma once
#include <string>
class ActionTrigger
{
public:
	ActionTrigger(std::string trigger_name, std::string effect_factory_name);
	std::string trigger_name;
	std::string effect_factory_name;
};

