#include "VisorEffectAction.h"
#include "VisorEffect.h"
VisorEffectAction::VisorEffectAction(double speed, RGBColor color)
{
	_speed = speed;
	_color = std::move(color);
}

void VisorEffectAction::add_new_instance(EffectManager& effect_manager)
{
	effect_manager.add_effect(std::make_unique<VisorEffect>(0, _speed, _color));
}
