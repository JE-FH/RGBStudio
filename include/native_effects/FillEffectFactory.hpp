#include <event_trigger_runner/IEffectFactory.hpp>

class FillEffectFactory : public IEffectFactory {
private:
	DynamicConfigSpec spec;
public:
	FillEffectFactory();

	std::unique_ptr<IEffect> create(const DynamicConfig& dynamic_config, std::shared_ptr<IKeyboardDevice> device) override;

	const DynamicConfigSpec& get_config_spec() const override;

	std::string get_name() const override;
};
