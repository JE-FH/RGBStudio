#include <event_trigger_runner/default_triggers/KeyTriggerFactory.hpp>
#include <event_trigger_runner/default_triggers/KeyTrigger.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>

KeyTriggerFactory::KeyTriggerFactory() {
	spec.add_field("trigger_key", std::make_unique<ConfigIntegerTypeDesc>(), true);
	spec.add_field("trigger_on_press", std::make_unique<ConfigBoolTypeDesc>(), false);
	spec.add_field("trigger_on_release", std::make_unique<ConfigBoolTypeDesc>(), false);
	spec.add_field("trigger_on_repeat", std::make_unique<ConfigBoolTypeDesc>(), false);
}

std::unique_ptr<Trigger> KeyTriggerFactory::create(std::string name, const DynamicConfig& dynamic_config) {
	auto trigger_key = dynamic_config.get_config_value<ConfigIntegerValue>("trigger_key");
	auto trigger_on_press = dynamic_config.get_optional_value<ConfigBoolValue>("trigger_on_press");
	auto trigger_on_release = dynamic_config.get_optional_value<ConfigBoolValue>("trigger_on_release");
	auto trigger_on_repeat = dynamic_config.get_optional_value<ConfigBoolValue>("trigger_on_repeat");
	
	return std::make_unique<KeyTrigger>(name, 
		trigger_key.get_value(), 
		trigger_on_press != nullptr && trigger_on_press->get_value(),
		trigger_on_release != nullptr && trigger_on_release->get_value(),
		trigger_on_repeat != nullptr && trigger_on_repeat->get_value()
	);
}

const DynamicConfigSpec& KeyTriggerFactory::get_config_spec() const {
	return spec;
}

std::string KeyTriggerFactory::get_name() const {
	return "Key trigger";
}
