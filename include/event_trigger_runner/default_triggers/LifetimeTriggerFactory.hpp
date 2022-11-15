#pragma once
#include "../ITriggerFactory.hpp"

class LifetimeTriggerFactory : public ITriggerFactory {
private:
    DynamicConfigSpec spec;
public:
    LifetimeTriggerFactory();
    std::unique_ptr<Trigger> create(std::string name, const DynamicConfig& dynamic_config) override;
	const DynamicConfigSpec& get_config_spec() const override;
	std::vector<std::string> get_sub_triggers() const;
	std::string get_name() const override;
};
