#include "editor.hpp"
#include "EncodingConverter.hpp"
#include <windows.h>
#include <stdexcept>
#include <fstream>
#include <codecvt>
#include <iostream>
Editor::Editor(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader) {
	this->hwnd = hwnd;
	this->asset_loader = std::move(asset_loader);
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
		Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(this, &Editor::environment_created).Get()
	);
}

void Editor::setup(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader) {
	Editor::instance = std::unique_ptr<Editor>(new Editor(hwnd, std::move(asset_loader)));
}

void Editor::set_bounds(RECT bounds)
{
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


HRESULT Editor::environment_created(HRESULT result, ICoreWebView2Environment* env) {
	env->CreateCoreWebView2Controller(hwnd, 
		Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &Editor::create_controller_completed).Get()
	);
	return S_OK;
}

HRESULT Editor::create_controller_completed(HRESULT result, ICoreWebView2Controller* controller)
{
	if (controller != nullptr) {
		webviewController = controller;
		webviewController->get_CoreWebView2(&webviewWindow);
	}

	// Add a few settings for the webview
	// The demo step is redundant since the values are the default settings
	ICoreWebView2Settings* Settings;
	webviewWindow->get_Settings(&Settings);
	Settings->put_IsScriptEnabled(TRUE);
	Settings->put_AreDefaultScriptDialogsEnabled(TRUE);
	Settings->put_IsWebMessageEnabled(TRUE);

	// Resize WebView to fit the bounds of the parent window
	RECT bounds;
	GetClientRect(hwnd, &bounds);
	webviewController->put_Bounds(bounds);

	/*webviewWindow->SetVirtualHostNameToFolderMapping(
		L"rgbeditor",
		L"file:///L:/Development/cpp/RGBStudio/src/RGBStudio/build",
		CoreWebView2HostResourceAccessKind.DenyCors
	);*/

	auto html = EncodingConverter::utf8_to_utf16(
		asset_loader->load_asset("assets/editor.html")
	);

	// Schedule an async task to navigate to 
	webviewWindow->NavigateToString((LPCWSTR) html.c_str());
	// Step 4 - Navigation events
	// register an ICoreWebView2NavigationStartingEventHandler to cancel any non-https navigation
	EventRegistrationToken token;
	webviewWindow->add_NavigationStarting(Microsoft::WRL::Callback<ICoreWebView2NavigationStartingEventHandler>(
		[](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
			PWSTR uri;
			args->get_Uri(&uri);
			std::wstring source(uri);
			if (source.substr(0, 14) != L"data:text/html") {
				args->put_Cancel(true);
			}
			CoTaskMemFree(uri);
			return S_OK;
		}).Get(), &token);

	// Step 5 - Scripting
	// Schedule an async task to add initialization script that freezes the Object object
	webviewWindow->AddScriptToExecuteOnDocumentCreated(L"Object.freeze(Object);", nullptr);
	// Schedule an async task to get the document URL
	webviewWindow->ExecuteScript(L"window.document.URL;", Microsoft::WRL::Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
		[](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
			LPCWSTR URL = resultObjectAsJson;
			//doSomethingWithURL(URL);
			return S_OK;
		}).Get());

	// Step 6 - Communication between host and web content
	// Set an event handler for the host to return received message back to the web content
	webviewWindow->add_WebMessageReceived(Microsoft::WRL::Callback<ICoreWebView2WebMessageReceivedEventHandler>(
		[](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
			PWSTR message;
			args->TryGetWebMessageAsString(&message);
			std::wcout << message << std::endl;
			std::wstring echo_message = L"Echo: " + std::wstring(message);
			webview->PostWebMessageAsString(echo_message.c_str());
			CoTaskMemFree(message);
			return S_OK;
		}).Get(), &token);

	return S_OK;
}


std::unique_ptr<Editor> Editor::instance = nullptr;
