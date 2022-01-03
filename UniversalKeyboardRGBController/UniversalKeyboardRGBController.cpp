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

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("space key press", VK_SPACE, true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("space key repeat", VK_SPACE, false, true, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("space key release", VK_SPACE, false, false, true));

	event_trigger_controller.add_effect_factory("red visor", std::make_unique<VisorEffectAction>(10, RGBColor{ 255, 0, 0 }));
	event_trigger_controller.add_effect_factory("green visor", std::make_unique<VisorEffectAction>(10, RGBColor{ 0, 255, 0 }));
	event_trigger_controller.add_effect_factory("blue visor", std::make_unique<VisorEffectAction>(10, RGBColor{ 0, 0, 255 }));

	event_trigger_controller.add_action_trigger("space key press", "red visor");
	event_trigger_controller.add_action_trigger("space key repeat", "green visor");
	event_trigger_controller.add_action_trigger("space key release", "blue visor");

	KeyboardEventSource::init();
	event_trigger_controller.run();
}

