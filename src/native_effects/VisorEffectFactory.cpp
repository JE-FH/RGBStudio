#include <native_effects/VisorEffectFactory.hpp>
#include <native_effects/VisorEffect.hpp>
VisorEffectAction::VisorEffectAction(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, double speed, RGBColor color)
{
	_layer = layer;
	_speed = speed;
	_color = std::move(color);
	_keyboard_device = std::move(keyboard_device);
}

void VisorEffectAction::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect(std::make_unique<VisorEffect>(_layer, _keyboard_device, _speed, _color));
}
