#include "FillEffect.h"

FillEffect::FillEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, std::string stop_trigger, RGBColor color, TriggerObserverDispatcher& trigger_observer_dispatcher)
	: Effect(layer, std::move(keyboard_device))
{
	_color = std::move(color);
	trigger_observer_dispatcher.add_observer(stop_trigger, *this);
}

void FillEffect::draw(double delta)
{
	_keyboard_device->fill(_color);
}

void FillEffect::Trigger(const std::string& trigger_name)
{
	this->mark_completed();
}