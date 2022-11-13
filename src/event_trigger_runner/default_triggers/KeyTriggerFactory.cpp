#include <event_trigger_runner/default_triggers/KeyTriggerFactory.hpp>
#include <event_trigger_runner/default_triggers/KeyTrigger.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>

KeyTriggerFactory::KeyTriggerFactory() {
	spec.add_field("trigger_key", std::make_unique<ConfigIntegerTypeDesc>(), true);
}

std::unique_ptr<Trigger> KeyTriggerFactory::create(std::string name, const DynamicConfig& dynamic_config) {
	auto& trigger_key = dynamic_config.get_config_value<ConfigIntegerValue>("trigger_key");
	
	return std::make_unique<KeyTrigger>(
		name, 
		(unsigned short) trigger_key.get_value()
	);
}

const DynamicConfigSpec& KeyTriggerFactory::get_config_spec() const {
	return spec;
}

std::vector<std::string> KeyTriggerFactory::get_sub_triggers() const {
	return std::vector<std::string> {
		"pressed",
		"released",
		"repeated"
	};
}

std::string KeyTriggerFactory::get_name() const {
	return "Key trigger";
}
