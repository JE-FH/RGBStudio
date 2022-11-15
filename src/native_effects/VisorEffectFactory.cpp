#include <native_effects/VisorEffectFactory.hpp>
#include <native_effects/VisorEffect.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>
#include <memory>

VisorEffectFactory::VisorEffectFactory() {
    spec.add_field("layer", std::make_unique<ConfigIntegerTypeDesc>(), true);
    spec.add_field("speed", std::make_unique<ConfigNumberTypeDesc>(), true);
    spec.add_field("color", std::make_unique<ConfigRGBColorTypeDesc>(), true);
}

std::unique_ptr<IEffect> VisorEffectFactory::create(const DynamicConfig& dynamic_config, std::shared_ptr<IKeyboardDevice> device) {
    auto& layer = dynamic_config.get_config_value<ConfigIntegerValue>("layer");
	auto& speed = dynamic_config.get_config_value<ConfigNumberValue>("speed");
	auto& color = dynamic_config.get_config_value<ConfigRGBColorValue>("color");

	return std::make_unique<VisorEffect>(layer.get_value(), device, speed.get_value(), color.get_value());

}

const DynamicConfigSpec& VisorEffectFactory::get_config_spec() const {
    return spec;
}

std::string VisorEffectFactory::get_name() const {
    return "Visor effect";
}
