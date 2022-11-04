#include "Program.hpp"
#include <rpc/server.h>
#include <iostream>
#include <RGBLightRunner/HelloResponse.hpp>
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
#include <native_effects/FillEffectFactory.hpp>
#include <native_effects/VisorEffect.hpp>
#include <event_trigger_runner/IEffectFactory.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <event_trigger_runner/default_triggers/KeyTrigger.hpp>
#include <event_trigger_runner/default_triggers/KeyTriggerFactory.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>
#include <Objbase.h>

#include "RGBLightRunner/RGBLightRunnerConfig.hpp"
#include "RGBLightRunner/RGBLightRunnerTrigger.hpp"
#include "RGBLightRunner/RGBLightRunnerEffect.hpp"

class RGBLightRunner {
	std::unique_ptr<EventTriggerController> _eventTriggerController;
	std::vector<std::unique_ptr<ITriggerFactory>> _triggerFactories;
	std::vector<std::unique_ptr<IEffectFactory>> _effectFactories;
public:
	RGBLightRunner(const RGBLightRunner&) = delete;
	RGBLightRunner(RGBLightRunner&&) = delete;

	RGBLightRunner(std::shared_ptr<IKeyboardDevice> keyboardDevice) {
		AddFactories();

		auto effectManager = EffectManager();
		effectManager.add_device(keyboardDevice);

		auto eventManager = EventManager();
		eventManager.add_event_source(std::make_unique<KeyboardEventSource>());

		_eventTriggerController = std::make_unique<EventTriggerController>(std::move(effectManager), std::move(eventManager));
	}

	void Run() {

		rpc::server rpcServer(8080);

		rpcServer.bind("Hello", [&]() { return HelloCommand(); });
		rpcServer.bind("ListTriggers", [&]() { return ListTriggersCommand(); });
		rpcServer.bind("ListEffects", [&]() { return ListEffectsCommand(); });

		rpcServer.async_run();
	
		InitEventSources();

		while (true) {
			_eventTriggerController->run_tick();
		}
	}

	HelloResponse HelloCommand() {
		return HelloResponse{
				.major = 0,
				.minor = 1
		};
	}

	std::vector<RGBLightRunnerTrigger> ListTriggersCommand() {
		std::vector<RGBLightRunnerTrigger> rv;
		for (const auto& trigger : _triggerFactories)
		{
			RGBLightRunnerTrigger triggerDesc;
			triggerDesc.id = trigger->get_name();
			auto& spec = trigger->get_config_spec();
			for (const auto& field : spec.get_fields()) {
				triggerDesc.attributes.push_back(RGBLightRunnerAttributeDescription{
					.name = field.name,
					.type = field.type_desc->get_internal_name()
				});
			}
			rv.push_back(std::move(triggerDesc));
		}
		return rv;
	}

	std::vector<RGBLightRunnerEffect> ListEffectsCommand() {
		std::vector<RGBLightRunnerEffect> rv;
		for (const auto& effect : _effectFactories) {
			RGBLightRunnerEffect effectDesc;
			effectDesc.id = effect->get_name();
			auto& spec = effect->get_config_spec();
			for (const auto& field : spec.get_fields()) {
				effectDesc.attributes.push_back(RGBLightRunnerAttributeDescription{
					.name = field.name,
					.type = field.type_desc->get_internal_name()
					});
			}
			rv.push_back(std::move(effectDesc));
		}
		return rv;
	}

private:
	void AddFactories() {
		_triggerFactories.push_back(std::make_unique<KeyTriggerFactory>());
		_effectFactories.push_back(std::make_unique<FillEffectFactory>());
	}

	void InitEventSources() {
		KeyboardEventSource::init();
	}
};

int Program::Main(std::span<char*> arguments)
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

	std::cout << "Starting RPC server" << std::endl;

	RGBLightRunner lightRunner(keyboard_device);

	lightRunner.Run();

	return 0;
}
