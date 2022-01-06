#include "FillEffect.h"

FillEffect::FillEffect(int layer, std::string stop_trigger, RGBColor color, TriggerObserverDispatcher& trigger_observer_dispatcher)
	: Effect(layer)
{
	_color = std::move(color);
	trigger_observer_dispatcher.add_observer(stop_trigger, *this);
}

void FillEffect::draw(IKeyboardDevice* device, double delta)
{
	device->fill(_color);
}

void FillEffect::Trigger(std::string trigger_name)
{
	this->mark_completed();
}