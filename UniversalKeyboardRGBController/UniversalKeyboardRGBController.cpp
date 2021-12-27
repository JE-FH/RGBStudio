#include <iostream>
#include "ASUSAuraDeviceFactory.h"
#include "VisorEffectAction.h"
#include "EffectManager.h"
#include "EventTriggerController.h"
#include "KeyboardEventSource.h"
#include "KeyTrigger.h"
int main()
{
	auto device_factory = std::make_unique<ASUSAuraDeviceFactory>();

	auto effect_manager = EffectManager(device_factory->create_keyboard_device());

	auto event_trigger_controller = EventTriggerController(std::move(effect_manager));
	event_trigger_controller.add_event_source(std::make_unique<KeyboardEventSource>());

	auto test_trigger = std::make_unique<KeyTrigger>(VK_SPACE);
	test_trigger->add_action(std::make_shared<VisorEffectAction>(10, RGBColor {255, 0, 0}));

	event_trigger_controller.add_trigger(std::move(test_trigger));

	KeyboardEventSource::init();
	event_trigger_controller.run();
}

