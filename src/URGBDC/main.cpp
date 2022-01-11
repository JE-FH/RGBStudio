#include <effect_manager/EffectManager.hpp>
#include <asus_aura_adapter/ASUSAuraDeviceFactory.hpp>
#include <native_effects/VisorEffect.hpp>
#include <lua_effect_loader/LuaEffect.hpp>
#include <lua_effect_loader/LuaEffectFactory.hpp>
#include <lua_effect_loader/LuaEffectSettings.hpp>
#include <lua_effect_loader/LuaIntegerValue.hpp>
#include <lua_effect_loader/LuaStringValue.hpp>
#include <lua_effect_loader/LuaNumberValue.hpp>
#include <event_trigger_runner/EventManager.hpp>
#include <event_trigger_runner/EventTriggerController.hpp>
#include <windows_event_sources/KeyboardEventSource.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "KeyTrigger.hpp"

std::unique_ptr<LuaEffectFactory> fraction_effect(std::shared_ptr<IKeyboardDevice> keyboard_device, RGBColor color, std::string end_trigger, lua_Number start, lua_Number end) {
	LuaEffectSettings lua_effect_settings;
	lua_effect_settings.set_setting("red", std::make_unique<LuaIntegerValue>(color.r));
	lua_effect_settings.set_setting("green", std::make_unique<LuaIntegerValue>(color.g));
	lua_effect_settings.set_setting("blue", std::make_unique<LuaIntegerValue>(color.b));
	lua_effect_settings.set_setting("end_trigger", std::make_unique<LuaStringValue>(end_trigger));
	lua_effect_settings.set_setting("start_fraction", std::make_unique<LuaNumberValue>(start));
	lua_effect_settings.set_setting("end_fraction", std::make_unique<LuaNumberValue>(end));

	return std::make_unique<LuaEffectFactory>(0, keyboard_device, "effect.lua", lua_effect_settings);
}

int catched_main()
{
	std::cout << "Connecting to keyboard" << std::endl;
	auto device_factory = std::make_unique<ASUSAuraDeviceFactory>();

	auto keyboard_device = device_factory->create_keyboard_device();

	auto effect_manager = EffectManager();
	effect_manager.add_device(keyboard_device);

	auto event_manager = EventManager();
	event_manager.add_event_source(std::make_unique<KeyboardEventSource>());

	auto event_trigger_controller = EventTriggerController(std::move(effect_manager), std::move(event_manager));

	std::cout << "Creating effects and triggers" << std::endl;

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("escape key press", VK_ESCAPE, true, false, false));

	event_trigger_controller.add_effect_factory("green highlight", fraction_effect(keyboard_device, RGBColor{ 0, 255, 0 }, "green highlight stop", 0, 0.2));
	event_trigger_controller.add_effect_factory("red highlight", fraction_effect(keyboard_device, RGBColor{ 255, 0, 0 }, "red highlight stop", 0.2, 0.4));
	event_trigger_controller.add_effect_factory("yellow highlight", fraction_effect(keyboard_device, RGBColor{ 255, 255, 0 }, "yellow highlight stop", 0.4, 0.6));
	event_trigger_controller.add_effect_factory("blue highlight", fraction_effect(keyboard_device, RGBColor{ 0, 0, 255 }, "blue highlight stop", 0.6, 0.8));
	event_trigger_controller.add_effect_factory("orange highlight", fraction_effect(keyboard_device, RGBColor{ 255, 106, 0 }, "orange highlight stop", 0.8, 1));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("green key press", 'A', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("green key release", 'A', false, true, false));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("red key press", 'S', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("red key release", 'S', false, true, false));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("yellow key press", 'D', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("yellow key release", 'D', false, true, false));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("blue key press", 'F', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("blue key release", 'F', false, true, false));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("orange key press", 'G', true, false, false));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("orange key release", 'G', false, true, false));

	event_trigger_controller.add_action_trigger("green key press", "green highlight");
	event_trigger_controller.add_action_trigger("red key press", "red highlight");
	event_trigger_controller.add_action_trigger("yellow key press", "yellow highlight");
	event_trigger_controller.add_action_trigger("blue key press", "blue highlight");
	event_trigger_controller.add_action_trigger("orange key press", "orange highlight");

	event_trigger_controller.add_action_trigger("green key release", "green highlight stop");
	event_trigger_controller.add_action_trigger("red key release", "red highlight stop");
	event_trigger_controller.add_action_trigger("yellow key release", "yellow highlight stop");
	event_trigger_controller.add_action_trigger("blue key release", "blue highlight stop");
	event_trigger_controller.add_action_trigger("orange key release", "orange highlight stop");

	std::cout << "Starting event loop" << std::endl;

	KeyboardEventSource::init();

	
	event_trigger_controller.run();
	
	return 0;
}

int main() {
	try {
		return catched_main();
	} catch (const std::exception& e) {
		std::cout << "Exception: " << e.what();
		return 1;
	}
}