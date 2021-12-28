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

	auto press_trigger = std::make_unique<KeyTrigger>(VK_SPACE, true, false, false);
	press_trigger->add_action(std::make_shared<VisorEffectAction>(10, RGBColor {255, 0, 0}));
	
	auto release_trigger = std::make_unique<KeyTrigger>(VK_SPACE, false, true, false);
	release_trigger->add_action(std::make_shared<VisorEffectAction>(10, RGBColor{ 0, 255, 0 }));

	auto repeat_trigger = std::make_unique<KeyTrigger>(VK_SPACE, false, false, true);
	repeat_trigger->add_action(std::make_shared<VisorEffectAction>(10, RGBColor{ 0, 0, 255 }));

	event_trigger_controller.add_trigger(std::move(press_trigger));
	event_trigger_controller.add_trigger(std::move(release_trigger));
	event_trigger_controller.add_trigger(std::move(repeat_trigger));

	KeyboardEventSource::init();
	event_trigger_controller.run();
}

