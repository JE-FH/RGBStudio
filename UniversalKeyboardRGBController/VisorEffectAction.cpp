#include "VisorEffectAction.h"
#include "VisorEffect.h"
VisorEffectAction::VisorEffectAction(double speed, RGBColor color)
{
	_speed = speed;
	_color = std::move(color);
}

void VisorEffectAction::do_effect(EffectManager& effect_manager)
{
	effect_manager.add_effect(std::make_unique<VisorEffect>(_speed, _color));
}
