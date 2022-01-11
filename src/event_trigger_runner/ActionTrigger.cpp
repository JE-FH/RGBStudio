#include "ActionTrigger.h"

ActionTrigger::ActionTrigger(std::string trigger_name, std::string effect_factory_name)
{
	this->trigger_name = std::move(trigger_name);
	this->effect_factory_name = std::move(effect_factory_name);
}
