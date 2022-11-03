#include <native_effects/FillEffectFactory.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>
#include <memory>
#include "native_effects/FillEffect.hpp"

FillEffectFactory::FillEffectFactory() {
	spec.add_field("layer", std::make_unique<ConfigIntegerTypeDesc>(), true);
	spec.add_field("stop trigger", std::make_unique<ConfigTriggerNameTypeDesc>(), true);
	spec.add_field("color", std::make_unique<ConfigRGBColorTypeDesc>(), true);
}

std::unique_ptr<IEffect> FillEffectFactory::create(const DynamicConfig& dynamic_config, std::shared_ptr<IKeyboardDevice> device) {
	auto& layer = dynamic_config.get_config_value<ConfigIntegerValue>("layer");
	auto& stop_trigger = dynamic_config.get_config_value<ConfigTriggerNameValue>("stop trigger");
	auto& color = dynamic_config.get_config_value<ConfigRGBColorValue>("color");

	return std::make_unique<FillEffect>(layer.get_value(), device, stop_trigger.get_value(), color.get_value());
}

const DynamicConfigSpec& FillEffectFactory::get_config_spec() const {
	return spec;
}

std::string FillEffectFactory::get_name() const {
	return "Fill effect";
}
