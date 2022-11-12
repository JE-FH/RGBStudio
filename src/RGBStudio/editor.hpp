#pragma once
#include "IAssetLoader.hpp"
#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>
#include <memory>
#include <event_trigger_runner/ITriggerFactory.hpp>
#include <stdexcept>
#include <iostream>
#include "JSONRPC.hpp"
#include "LightRunnerApi.hpp"

class Editor : public IJSONRPCConnection, public IJSONRPCSubscriber {
private:
	Editor(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader, std::unique_ptr<LightRunnerApi> lightRunnerApi);
	
	HWND hwnd;
	wil::com_ptr<ICoreWebView2Controller> webviewController;
	wil::com_ptr<ICoreWebView2> webviewWindow;
	static std::unique_ptr<Editor> instance;
	std::unique_ptr<IAssetLoader> asset_loader;
	std::unique_ptr<LightRunnerApi> _lightRunnerApi;

	EventRegistrationToken web_message_received_evt;
	EventRegistrationToken navigation_started_evt;
	bool is_browser_js_ready;

	JSONRPC json_rpc;

	void environment_created(HRESULT result, ICoreWebView2Environment* env);
	void create_controller_completed(HRESULT result, ICoreWebView2Controller* controller);

	void notify_browser_added_trigger(const RGBLightRunnerTrigger& added_trigger);
	void notify_browser_added_effect(const RGBLightRunnerEffect& added_effect);
	void ok_or_throw(HRESULT result);

	void browser_callback(std::wstring message);

	void command_ready();
public:
	~Editor();
	void set_bounds(RECT bounds);
	bool ready();
	static Editor& gi();
	static Editor* ogi();
	static void setup(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader, std::unique_ptr<LightRunnerApi> lightRunnerApi);

	void apply_config_command(const nlohmann::json& param);

	// Inherited via IJSONRPCConnection
	virtual void send_message(nlohmann::json message) override;

	// Inherited via IJSONRPCSubscriber
	virtual void received_call(int id, std::string method_name, nlohmann::json param) override;
};
