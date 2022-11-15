#pragma once
#include <event_trigger_runner/IEffectFactory.hpp>

class VisorEffectFactory : public IEffectFactory {
private:
    DynamicConfigSpec spec;
public:
    VisorEffectFactory();

    std::unique_ptr<IEffect> create(const DynamicConfig& dynamic_config, std::shared_ptr<IKeyboardDevice> device) override;

	const DynamicConfigSpec& get_config_spec() const override;

	std::string get_name() const override;
};
