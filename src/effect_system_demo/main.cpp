#include <effect_manager/EffectManager.hpp>
#include <native_effects/VisorEffectInstance.hpp>
#include <lua_effect_loader/LuaEffectInstance.hpp>
#include <lua_effect_loader/LuaEffect.hpp>
#include <lua_effect_loader/LuaEffectSettings.hpp>
#include <lua_effect_loader/LuaIntegerValue.hpp>
#include <lua_effect_loader/LuaStringValue.hpp>
#include <lua_effect_loader/LuaNumberValue.hpp>
#include <event_trigger_runner/EventManager.hpp>
#include <event_trigger_runner/EventTriggerController.hpp>
#include <windows_event_sources/KeyboardEventSource.hpp>
#include <device_adapter_loader/DeviceAdapter.hpp>
#include <device_adapter_loader/DeviceFactory.hpp>

#include <iostream>
#include <memory>
#include <stdexcept>

#include <event_trigger_runner/default_triggers/KeyTrigger.hpp>
#include <event_trigger_runner/default_triggers/KeyTriggerFactory.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>

std::unique_ptr<LuaEffect> fraction_effect(std::shared_ptr<IKeyboardDevice> keyboard_device, RGBColor color, std::string end_trigger, lua_Number start, lua_Number end) {
	LuaEffectSettings lua_effect_settings;
	lua_effect_settings.set_setting("red", std::make_unique<LuaIntegerValue>(color.r));
	lua_effect_settings.set_setting("green", std::make_unique<LuaIntegerValue>(color.g));
	lua_effect_settings.set_setting("blue", std::make_unique<LuaIntegerValue>(color.b));
	lua_effect_settings.set_setting("end_trigger", std::make_unique<LuaStringValue>(end_trigger));
	lua_effect_settings.set_setting("start_fraction", std::make_unique<LuaNumberValue>(start));
	lua_effect_settings.set_setting("end_fraction", std::make_unique<LuaNumberValue>(end));

	return std::make_unique<LuaEffect>(0, keyboard_device, "fill_fraction.lua", lua_effect_settings);
}

int catched_main()
{
	// Initialize COM
	HRESULT hr = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (!SUCCEEDED(hr))
	{
		// Uninitialize COM
		::CoUninitialize();
		throw std::exception("Could not initialize COM");
	}
	
	std::cout << "Enter path for device adapter (leave empty for asus_aura_adapter.dll): ";
	std::string path;
	std::getline(std::cin, path);

	if (path.size() == 0) {
		path = "asus_aura_adapter.dll";
	}
	auto device_adapter = std::make_shared<DeviceAdapter>(path.c_str());

	std::cout << "Connecting to keyboard" << std::endl;

	std::shared_ptr<IKeyboardDevice> keyboard_device;

	{
		DeviceFactory factory(device_adapter);
		auto devices = factory.create_devices();

		if (devices.size() == 0) {
			throw std::runtime_error("No connected devices");
		}

		keyboard_device = devices[0];
	}

	auto effect_manager = EffectManager();
	effect_manager.add_device(keyboard_device);

	auto event_manager = EventManager();
	event_manager.add_event_source(std::make_shared<KeyboardEventSource>());

	auto event_trigger_controller = EventTriggerController(std::move(effect_manager), std::move(event_manager));

	std::cout << "Creating effects and triggers" << std::endl;

	auto trigger_factory = KeyTriggerFactory();

	DynamicConfig dynamic_config;
	dynamic_config.set_config_value("trigger_key", std::make_unique<ConfigIntegerValue>('A'));
	dynamic_config.set_config_value("trigger_on_press", std::make_unique<ConfigBoolValue>(true));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("escape key", VK_ESCAPE));

	event_trigger_controller.add_effect("green highlight", fraction_effect(keyboard_device, RGBColor{ 0, 255, 0 }, "green highlight stop", 0, 0.2));
	event_trigger_controller.add_effect("red highlight", fraction_effect(keyboard_device, RGBColor{ 255, 0, 0 }, "red highlight stop", 0.2, 0.4));
	event_trigger_controller.add_effect("yellow highlight", fraction_effect(keyboard_device, RGBColor{ 255, 255, 0 }, "yellow highlight stop", 0.4, 0.6));
	event_trigger_controller.add_effect("blue highlight", fraction_effect(keyboard_device, RGBColor{ 0, 0, 255 }, "blue highlight stop", 0.6, 0.8));
	event_trigger_controller.add_effect("orange highlight", fraction_effect(keyboard_device, RGBColor{ 255, 106, 0 }, "orange highlight stop", 0.8, 1));

	event_trigger_controller.add_trigger(trigger_factory.create("green key press", dynamic_config));
	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("green key", 'A'));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("red key", 'S'));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("yellow key", 'D'));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("blue key", 'F'));

	event_trigger_controller.add_trigger(std::make_unique<KeyTrigger>("orange key", 'G'));

	event_trigger_controller.add_trigger_action_edge("green key.pressed", "green highlight");
	event_trigger_controller.add_trigger_action_edge("red key.pressed", "red highlight");
	event_trigger_controller.add_trigger_action_edge("yellow key.pressed", "yellow highlight");
	event_trigger_controller.add_trigger_action_edge("blue key.pressed", "blue highlight");
	event_trigger_controller.add_trigger_action_edge("orange key.pressed", "orange highlight");

	event_trigger_controller.add_trigger_action_edge("green key.released", "green highlight stop");
	event_trigger_controller.add_trigger_action_edge("red key.released", "red highlight stop");
	event_trigger_controller.add_trigger_action_edge("yellow key.released", "yellow highlight stop");
	event_trigger_controller.add_trigger_action_edge("blue key.released", "blue highlight stop");
	event_trigger_controller.add_trigger_action_edge("orange key.released", "orange highlight stop");

	event_trigger_controller.add_action_effect_edge("green highlight", "green highlight");
	event_trigger_controller.add_action_effect_edge("red highlight", "red highlight");
	event_trigger_controller.add_action_effect_edge("yellow highlight", "yellow highlight");
	event_trigger_controller.add_action_effect_edge("blue highlight", "blue highlight");
	event_trigger_controller.add_action_effect_edge("orange highlight", "orange highlight");

	event_trigger_controller.add_action_effect_edge("green highlight stop", "green highlight stop");
	event_trigger_controller.add_action_effect_edge("red highlight stop", "red highlight stop");
	event_trigger_controller.add_action_effect_edge("yellow highlight stop", "yellow highlight stop");
	event_trigger_controller.add_action_effect_edge("blue highlight stop", "blue highlight stop");
	event_trigger_controller.add_action_effect_edge("orange highlight stop", "orange highlight stop");


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