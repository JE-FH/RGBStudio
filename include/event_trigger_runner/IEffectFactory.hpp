#pragma once
#include "IEffect.hpp"
#include <dynamic_config/DynamicConfig.hpp>
#include <dynamic_config/DynamicConfigSpec.hpp>
#include <memory>

class IEffectFactory {
public:
	virtual ~IEffectFactory() {}

	virtual std::unique_ptr<IEffect> create(const DynamicConfig& dynamic_config, std::shared_ptr<IKeyboardDevice> device) = 0;

	virtual const DynamicConfigSpec& get_config_spec() const = 0;

	virtual std::string get_name() const = 0;
};
