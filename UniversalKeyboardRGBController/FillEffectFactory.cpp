#include "FillEffectFactory.h"
#include "FillEffect.h"

FillEffectFactory::FillEffectFactory(int layer, std::string stop_trigger, RGBColor color)
{
	_layer = layer;
	_stop_trigger = stop_trigger;
	_color = color;
}

void FillEffectFactory::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect(std::make_unique<FillEffect>(_layer, _stop_trigger, _color, trigger_observer_dispatcher));
}
