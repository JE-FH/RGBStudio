#pragma once
#include "../ITriggerFactory.hpp"


class KeyTriggerFactory : ITriggerFactory {
private:
	DynamicConfigSpec spec;
public:
	KeyTriggerFactory();
	std::unique_ptr<Trigger> create(std::string name, const DynamicConfig& dynamic_config);
	const DynamicConfigSpec& get_config_spec();
};