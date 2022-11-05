#include <native_effects/VisorEffect.hpp>
#include <native_effects/VisorEffectInstance.hpp>
VisorEffect::VisorEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, double speed, RGBColor color)
{
	_layer = layer;
	_speed = speed;
	_color = std::move(color);
	_keyboard_device = std::move(keyboard_device);
}

void VisorEffect::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect_instance(std::make_unique<VisorEffectInstance>(_layer, _keyboard_device, _speed, _color));
}
