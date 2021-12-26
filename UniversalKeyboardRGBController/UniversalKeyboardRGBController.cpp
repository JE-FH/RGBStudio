#include <iostream>
#include "ASUSAuraDeviceFactory.h"
#include "VisorEffect.h"
#include "EffectManager.h"
int main()
{
	auto device_factory = std::make_unique<ASUSAuraDeviceFactory>();

	auto effect_manager = EffectManager(device_factory->create_keyboard_device());

	effect_manager.add_effect(std::make_unique<VisorEffect>(3, RGBColor{ 255, 255, 255 }));
	
	while (true) {
		effect_manager.tick();
	}
}

