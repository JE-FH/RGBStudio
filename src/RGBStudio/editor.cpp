#include "editor.hpp"
#include "EncodingConverter.hpp"
#include "COMCallbackExceptionProtection.hpp"
#include "Win32Error.hpp"
#include <windows.h>
#include <stdexcept>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <comdef.h>
#include <nlohmann/json.hpp>

Editor::Editor(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader, std::unique_ptr<LightRunnerApi> lightRunnerApi)
	: json_rpc(this)
{
	this->hwnd = hwnd;
	this->asset_loader = std::move(asset_loader);
	this->is_browser_js_ready = false;
	ok_or_throw(CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
		Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(COMCallbackExceptionProtection([&](HRESULT result, ICoreWebView2Environment* env) -> void {
			environment_created(result, env);
		})).Get()
	));
	json_rpc.subscribe(*this);
	_lightRunnerApi = std::move(lightRunnerApi);
}

Editor::~Editor()
{
	//We should not throw from the destructor so we just assume this works as expected and ignore errors
	//I dont know what else you could do
	webviewWindow->remove_NavigationStarting(navigation_started_evt);
	webviewWindow->remove_WebMessageReceived(web_message_received_evt);
}

void Editor::setup(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader, std::unique_ptr<LightRunnerApi> lightRunnerApi) {
	Editor::instance = std::unique_ptr<Editor>(new Editor(hwnd, std::move(asset_loader), std::move(lightRunnerApi)));
}

void Editor::send_message(nlohmann::json message) {
	if (!is_browser_js_ready) {
		throw std::runtime_error("tried to use json rpc before browser is ready");
	}
	auto json_string = EncodingConverter::utf8_to_utf16(message.dump());
	this->webviewWindow->PostWebMessageAsJson((LPCWSTR)json_string.c_str());
}

void Editor::received_call(int id, std::string method_name, nlohmann::json param) {
	if (method_name == "ready") {
		command_ready();
	}
}

void Editor::set_bounds(RECT bounds) {
	if (webviewController == nullptr) {
		throw new std::runtime_error("Cannot set bounds since editor isnt ready");
	}
	//TODO: check error here
	webviewController->put_Bounds(bounds);
}

bool Editor::ready()
{
	return webviewController != nullptr;
}

Editor& Editor::gi() {
	if (Editor::instance == nullptr) {
		throw std::runtime_error("Editor class needs to be setup first");
	}
	return *instance;
}

Editor* Editor::ogi()
{
	return instance.get();
}


void Editor::environment_created(HRESULT result, ICoreWebView2Environment* env) {
	ok_or_throw(result);

	ok_or_throw(env->CreateCoreWebView2Controller(hwnd, 
		Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
			COMCallbackExceptionProtection([&](HRESULT result, ICoreWebView2Controller* controller) -> void {
				create_controller_completed(result, controller);
			})
		).Get()
	));
}

void Editor::create_controller_completed(HRESULT result, ICoreWebView2Controller* controller) {
	ok_or_throw(result);

	if (controller != nullptr) {
		webviewController = controller;
		ok_or_throw(webviewController->get_CoreWebView2(&webviewWindow));
	}

	// Add a few settings for the webview
	// The demo step is redundant since the values are the default settings
	ICoreWebView2Settings* Settings;
	ok_or_throw(webviewWindow->get_Settings(&Settings));
	ok_or_throw(Settings->put_IsScriptEnabled(TRUE));
	ok_or_throw(Settings->put_AreDefaultScriptDialogsEnabled(TRUE));
	ok_or_throw(Settings->put_IsWebMessageEnabled(TRUE));

	// Resize WebView to fit the bounds of the parent window
	RECT bounds;
	GetClientRect(hwnd, &bounds);
	ok_or_throw(webviewController->put_Bounds(bounds));

	/*webviewWindow->SetVirtualHostNameToFolderMapping(
		L"rgbeditor",
		L"file:///L:/Development/cpp/RGBStudio/src/RGBStudio/build",
		CoreWebView2HostResourceAccessKind.DenyCors
	);*/

	auto html = EncodingConverter::utf8_to_utf16(
		asset_loader->load_asset("assets/editor.html")
	);

	// Schedule an async task to navigate to 
	ok_or_throw(webviewWindow->NavigateToString((LPCWSTR) html.c_str()));

	ok_or_throw(webviewWindow->add_NavigationStarting(Microsoft::WRL::Callback<ICoreWebView2NavigationStartingEventHandler>(
		 COMCallbackExceptionProtection([&](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> void {
			PWSTR uri;
			ok_or_throw(args->get_Uri(&uri));
			std::wstring source(uri);
			if (source.substr(0, 14) != L"data:text/html") {
				ok_or_throw(args->put_Cancel(true));
			}
			CoTaskMemFree(uri);
		})).Get(), &navigation_started_evt));

	// Step 6 - Communication between host and web content
	// Set an event handler for the host to return received message back to the web content
	ok_or_throw(webviewWindow->add_WebMessageReceived(Microsoft::WRL::Callback<ICoreWebView2WebMessageReceivedEventHandler>(
		COMCallbackExceptionProtection([&](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> void {
			PWSTR message;
			ok_or_throw(args->TryGetWebMessageAsString(&message));
			std::wstring message_copy = std::wstring(message);
			CoTaskMemFree(message);
			std::wcout << message_copy << std::endl;
			browser_callback(message_copy);
		})).Get(), &web_message_received_evt));
}

void Editor::notify_browser_added_trigger(const RGBLightRunnerTrigger& added_trigger) {
	nlohmann::json params;
	params["fields"] = nlohmann::json();
	params["name"] = added_trigger.id;
	for (const auto& field : added_trigger.attributes) {
		nlohmann::json field_desc;
		field_desc["name"] = field.name;
		field_desc["type"] = field.type;
		params["fields"][field.name] = field_desc;
	}

	json_rpc.call("AddedTrigger", params);
}

void Editor::notify_browser_added_effect(const RGBLightRunnerEffect& added_effect)
{
	nlohmann::json params;
	params["fields"] = nlohmann::json();
	params["name"] = added_effect.id;
	for (const auto& field : added_effect.attributes) {
		nlohmann::json field_desc;
		field_desc["name"] = field.name;
		field_desc["type"] = field.type;
		params["fields"][field.name] = field_desc;
	}

	json_rpc.call("AddedEffect", params);
}

void Editor::ok_or_throw(HRESULT result) {
	if (result != S_OK) {
		throw Win32Error(result);
	}
}

void Editor::browser_callback(std::wstring message) {
	try {
		auto parsed = nlohmann::json::parse(message);
		json_rpc.received_message(parsed);
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::cout << "Browser message was not valid json" << std::endl;
	}
}

void Editor::command_ready() {
	is_browser_js_ready = true;

	auto triggers = _lightRunnerApi->ListTriggers();
	for (auto& trigger : triggers) {
		notify_browser_added_trigger(trigger);
	}

	auto effects = _lightRunnerApi->ListEffects();
	for (auto& effect : effects) {
		notify_browser_added_effect(effect);
	}
}


std::unique_ptr<Editor> Editor::instance = nullptr;

Win32Error::Win32Error(HRESULT result)
{
	this->result = result;
	_com_error err(this->result);
	error_message = err.ErrorMessage();
}

const char* Win32Error::what() const {
	return error_message.c_str();
}
