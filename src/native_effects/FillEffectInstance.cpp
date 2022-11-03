#include <native_effects/FillEffectInstance.hpp>

FillEffectInstance::FillEffectInstance(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, std::string stop_trigger, RGBColor color, TriggerObserverDispatcher& trigger_observer_dispatcher)
	: EffectInstance(layer, std::move(keyboard_device))
{
	_color = std::move(color);
	trigger_observer_dispatcher.add_observer(stop_trigger, *this);
}

void FillEffectInstance::draw(double delta)
{
	for (auto it = _keyboard_device->key_begin(); it != _keyboard_device->key_end(); it++) {
		it->color = _color;
	}
}

void FillEffectInstance::Trigger(const std::string& trigger_name)
{
	this->mark_completed();
}