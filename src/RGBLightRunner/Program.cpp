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
#include <event_trigger_runner/IEffect.hpp>
#include <windows_event_sources/KeyboardEventSource.hpp>
#include <device_adapter_loader/DeviceAdapter.hpp>
#include <device_adapter_loader/DeviceFactory.hpp>
#include <native_effects/FillEffectFactory.hpp>
#include <native_effects/VisorEffect.hpp>
#include <event_trigger_runner/IEffectFactory.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <queue>
#include <event_trigger_runner/default_triggers/KeyTrigger.hpp>
#include <event_trigger_runner/default_triggers/KeyTriggerFactory.hpp>
#include <dynamic_config/ConfigGenericValue.hpp>
#include <Objbase.h>
#include <variant>
#include <mutex>
#include "RGBLightRunner/RGBLightRunnerConfig.hpp"
#include "RGBLightRunner/RGBLightRunnerTrigger.hpp"
#include "RGBLightRunner/RGBLightRunnerEffect.hpp"

struct ApplyConfigCommandData {
	RGBLightRunnerConfig config;
};


class RGBLightRunner {
	std::unique_ptr<EventTriggerController> _eventTriggerController;
	std::map<std::string, std::unique_ptr<ITriggerFactory>> _triggerFactories;
	std::map<std::string, std::unique_ptr<IEffectFactory>> _effectFactories;
	std::mutex _commandQueueLock;
	std::queue<std::variant<ApplyConfigCommandData>> _commandQueue;
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
		rpcServer.bind("ApplyConfig", [&](RGBLightRunnerConfig config) { ApplyConfigCommand(config); });
		rpcServer.async_run();
	
		InitEventSources();

		Loop();
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
			triggerDesc.id = trigger.second->get_name();
			auto& spec = trigger.second->get_config_spec();
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
			effectDesc.id = effect.second->get_name();
			auto& spec = effect.second->get_config_spec();
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

	void ApplyConfigCommand(RGBLightRunnerConfig config) {
		std::lock_guard<std::mutex> guard(_commandQueueLock);
		_commandQueue.emplace(std::move(config));
	}

private:
	void AddFactories() {
		auto triggerFactory = std::make_unique<KeyTriggerFactory>();
		_triggerFactories.insert(std::pair(triggerFactory->get_name(), std::move(triggerFactory)));
		auto fillEffectFactory = std::make_unique<FillEffectFactory>();
		_effectFactories.insert(std::pair(fillEffectFactory->get_name(), std::move(fillEffectFactory)));
	}

	void InitEventSources() {
		KeyboardEventSource::init();
	}

	void Loop() {
		while (true) {
			EmptyCommandQueue();

			_eventTriggerController->run_tick();
		}
	}

	void EmptyCommandQueue() {
		std::lock_guard<std::mutex> guard(_commandQueueLock);
		while (_commandQueue.size() > 0) {
			auto& command = _commandQueue.front();
			if (std::holds_alternative<ApplyConfigCommandData>(command)) {
				ApplyConfig(std::get<ApplyConfigCommandData>(command).config);
			}
			_commandQueue.pop();
		}
	}

	void ApplyConfig(RGBLightRunnerConfig config) {
		_eventTriggerController->clear();
		for (const auto& edge : config.triggerActionEdges) {
			_eventTriggerController->add_trigger_action_edge(edge.first, edge.second);
		}

		for (const auto& edge : config.actionEffectEdges) {
			_eventTriggerController->add_action_effect_edge(edge.first, edge.second);
		}

		for (const auto& triggerInstanceConfig : config.triggerInstances) {
			const auto& triggerFactory = _triggerFactories.find(triggerInstanceConfig.triggerId);
			if (triggerFactory == _triggerFactories.end()) {
				//Todo: Report this error better
				std::cout << "Tried to create instance of non existant trigger " << triggerInstanceConfig.triggerId << std::endl;
				continue;
			}
			const auto& spec = triggerFactory->second->get_config_spec();
		}
	}

	DynamicConfig CreateDynamicConfigFromSpec(const DynamicConfigSpec& spec, const std::vector<InstanceDynamicAttribute>& attributes) {
		auto fields = spec.get_fields();
		
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
