#include <event_trigger_runner/IEffectFactory.hpp>
#include <string>
#include <memory>

class LuaEffectFactory : public IEffectFactory {
public:
	LuaEffectFactory(std::string _file_name);

	// Inherited via IEffectFactory
	virtual std::unique_ptr<IEffect> create(const DynamicConfig& dynamic_config, std::shared_ptr<IKeyboardDevice> device) override;
	virtual const DynamicConfigSpec& get_config_spec() const override;
	virtual std::string get_name() const override;

private:
	DynamicConfigSpec config_spec;
	std::string file_name;
	std::string given_name;
};