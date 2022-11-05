#include <native_effects/FillEffect.hpp>
#include <native_effects/FillEffectInstance.hpp>

FillEffect::FillEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, std::string stop_trigger, RGBColor color)
{
	_layer = layer;
	_stop_trigger = stop_trigger;
	_color = color;
	_keyboard_device = std::move(keyboard_device);
}

void FillEffect::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect_instance(std::make_unique<FillEffectInstance>(_layer, _keyboard_device, _stop_trigger, _color, trigger_observer_dispatcher));
}
