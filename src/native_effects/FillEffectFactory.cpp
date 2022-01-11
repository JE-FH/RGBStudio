#include <native_effects/FillEffectFactory.hpp>
#include <native_effects/FillEffect.hpp>

FillEffectFactory::FillEffectFactory(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, std::string stop_trigger, RGBColor color)
{
	_layer = layer;
	_stop_trigger = stop_trigger;
	_color = color;
	_keyboard_device = std::move(keyboard_device);
}

void FillEffectFactory::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect(std::make_unique<FillEffect>(_layer, _keyboard_device, _stop_trigger, _color, trigger_observer_dispatcher));
}
