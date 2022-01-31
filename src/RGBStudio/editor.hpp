#pragma once
#include "IAssetLoader.hpp"
#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>
#include <memory>

class Editor {
private:
	Editor(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader);

	HWND hwnd;
	wil::com_ptr<ICoreWebView2Controller> webviewController;
	wil::com_ptr<ICoreWebView2> webviewWindow;
	static std::unique_ptr<Editor> instance;
	std::unique_ptr<IAssetLoader> asset_loader;

	HRESULT environment_created(HRESULT result, ICoreWebView2Environment* env);
	HRESULT create_controller_completed(HRESULT result, ICoreWebView2Controller* controller);

public:
	void set_bounds(RECT bounds);
	bool ready();
	static Editor& gi();
	static Editor* ogi();
	static void setup(HWND hwnd, std::unique_ptr<IAssetLoader> asset_loader);
};
