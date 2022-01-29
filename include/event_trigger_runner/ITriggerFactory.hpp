#pragma once
#include "Trigger.hpp"
#include <dynamic_config/DynamicConfig.hpp>
#include <dynamic_config/DynamicConfigSpec.hpp>
#include <memory>

class ITriggerFactory {
public:
	virtual ~ITriggerFactory() {}

	virtual std::unique_ptr<Trigger> create(std::string name, const DynamicConfig& dynamic_config) = 0;

	virtual const DynamicConfigSpec& get_config_spec() = 0;
};
