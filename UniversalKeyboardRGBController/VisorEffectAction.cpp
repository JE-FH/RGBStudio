#include "VisorEffectAction.h"
#include "VisorEffect.h"
VisorEffectAction::VisorEffectAction(int layer, double speed, RGBColor color)
{
	_layer = layer;
	_speed = speed;
	_color = std::move(color);
}

void VisorEffectAction::add_new_instance(EffectManager& effect_manager, TriggerObserverDispatcher& trigger_observer_dispatcher)
{
	effect_manager.add_effect(std::make_unique<VisorEffect>(_layer, _speed, _color));
}
