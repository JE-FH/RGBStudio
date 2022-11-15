#include <event_trigger_runner/default_triggers/LifetimeTriggerFactory.hpp>
#include <event_trigger_runner/default_triggers/LifetimeTrigger.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>
#include <memory>
LifetimeTriggerFactory::LifetimeTriggerFactory() {
    
}

std::unique_ptr<Trigger> LifetimeTriggerFactory::create(std::string name, const DynamicConfig& dynamic_config) {
    return std::make_unique<LifetimeTrigger>(name);
}

const DynamicConfigSpec& LifetimeTriggerFactory::get_config_spec() const {
    return spec;
}

std::vector<std::string> LifetimeTriggerFactory::get_sub_triggers() const {
    return std::vector<std::string> {
        "starting",
        "stopping"
    };
}

std::string LifetimeTriggerFactory::get_name() const {
    return "Lifetime trigger";
}
