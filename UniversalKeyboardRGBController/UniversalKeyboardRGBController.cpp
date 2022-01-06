#include <iostream>
#include "ASUSAuraDeviceFactory.h"
#include "VisorEffectAction.h"
#include "EffectManager.h"
#include "EventTriggerController.h"
#include "KeyboardEventSource.h"
#include "KeyTrigger.h"
#include "FillEffectFactory.h"
#include "LuaEffectFactory.h"
#include "LuaIntegerValue.h"
#include "LuaNumberValue.h"
int main()
{
	auto device_factory = std::make_unique<ASUSAuraDeviceFactory>();

	auto effect_manager = EffectManager(device_factory->create_keyboard_device());

	auto event_manager = EventManager();
	event_manager.add_event_source(std::make_unique<KeyboardEventSource>());

	auto event_trigger_controller = EventTriggerController(std::move(effect_manager), std::move(event_manager));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("space key press", VK_SPACE, true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("space key release", VK_SPACE, false, true, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("space key repeat", VK_SPACE, false, false, true));

	event_trigger_controller.add_effect_factory("white background", std::make_unique<FillEffectFactory>(1, "white background stop", RGBColor{ 255, 255, 255 }));
	event_trigger_controller.add_effect_factory("red visor", std::make_unique<VisorEffectAction>(2, 10, RGBColor{ 255, 0, 0 }));
	event_trigger_controller.add_effect_factory("green visor", std::make_unique<VisorEffectAction>(2, 10, RGBColor{ 0, 255, 0 }));
	event_trigger_controller.add_effect_factory("blue visor", std::make_unique<VisorEffectAction>(2, 10, RGBColor{ 0, 0, 255 }));

	event_trigger_controller.add_action_trigger("space key press", "red visor");
	event_trigger_controller.add_action_trigger("space key repeat", "green visor");
	event_trigger_controller.add_action_trigger("space key release", "blue visor");

	event_trigger_controller.add_action_trigger("space key press", "white background");
	event_trigger_controller.add_action_trigger("space key release", "white background stop");

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("escape key press", VK_ESCAPE, true, false, false));
	
	LuaEffectSettings lua_effect_settings;
	lua_effect_settings.set_setting("red", std::make_unique<LuaIntegerValue>(0));
	lua_effect_settings.set_setting("green", std::make_unique<LuaIntegerValue>(255));
	lua_effect_settings.set_setting("blue", std::make_unique<LuaIntegerValue>(0));
	lua_effect_settings.set_setting("time", std::make_unique<LuaNumberValue>(1.5));

	event_trigger_controller.add_effect_factory("lua example effect", std::make_unique<LuaEffectFactory>(0, "effect.lua", lua_effect_settings));
	event_trigger_controller.add_action_trigger("escape key press", "lua example effect");

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("green key press", 'A', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("green key release", 'A', false, true, false));
	event_trigger_controller.add_effect_factory("green background", std::make_unique<FillEffectFactory>(0, "green background stop", RGBColor{ 0, 255, 0 }));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("red key press", 'S', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("red key release", 'S', false, true, false));
	event_trigger_controller.add_effect_factory("red background", std::make_unique<FillEffectFactory>(0, "red background stop", RGBColor{ 255, 0, 0 }));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("yellow key press", 'D', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("yellow key release", 'D', false, true, false));
	event_trigger_controller.add_effect_factory("yellow background", std::make_unique<FillEffectFactory>(0, "yellow background stop", RGBColor{ 255, 255, 0 }));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("blue key press", 'F', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("blue key release", 'F', false, true, false));
	event_trigger_controller.add_effect_factory("blue background", std::make_unique<FillEffectFactory>(0, "blue background stop", RGBColor{ 0, 0, 255 }));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("orange key press", 'G', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("orange key release", 'G', false, true, false));
	event_trigger_controller.add_effect_factory("orange background", std::make_unique<FillEffectFactory>(0, "orange background stop", RGBColor{ 255, 128, 0 }));

	event_trigger_controller.add_action_trigger("green key press", "green background");
	event_trigger_controller.add_action_trigger("red key press", "red background");
	event_trigger_controller.add_action_trigger("yellow key press", "yellow background");
	event_trigger_controller.add_action_trigger("blue key press", "blue background");
	event_trigger_controller.add_action_trigger("orange key press", "orange background");

	event_trigger_controller.add_action_trigger("green key release", "green background stop");
	event_trigger_controller.add_action_trigger("red key release", "red background stop");
	event_trigger_controller.add_action_trigger("yellow key release", "yellow background stop");
	event_trigger_controller.add_action_trigger("blue key release", "blue background stop");
	event_trigger_controller.add_action_trigger("orange key release", "orange background stop");



	KeyboardEventSource::init();
	event_trigger_controller.run();
}

