#include "KeyboardEventSource.h"
#include "KeyPressEvent.h"
#include "KeyReleaseEvent.h"
#include <Windows.h>
KeyboardEventSource::KeyboardEventSource()
{
	_keyboard_hooks.insert(this);
}

KeyboardEventSource::~KeyboardEventSource()
{
	_keyboard_hooks.erase(this);
}

KeyboardEventSource::KeyboardEventSource(KeyboardEventSource&& other) noexcept
{
	_keyboard_hooks.erase(this);
	_keyboard_hooks.insert(this);
}

void KeyboardEventSource::poll_events(EventQueue& event_queue)
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0) {    //this while loop keeps the hook
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	while (queued_events.size() > 0) {
		event_queue.push(std::move(queued_events.front()));
		queued_events.pop();
	}
}

void KeyboardEventSource::on_key_down(unsigned short code)
{
	queued_events.push(std::make_unique<KeyPressEvent>(code));
}

void KeyboardEventSource::on_key_up(unsigned short code)
{
	queued_events.push(std::make_unique<KeyReleaseEvent>(code));
}

void KeyboardEventSource::init()
{
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
}

std::set<KeyboardEventSource*> KeyboardEventSource::_keyboard_hooks;

LRESULT KeyboardEventSource::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
			printf("%x\n", p->dwExtraInfo);
			for (auto keyboard_event_source : _keyboard_hooks) {
				keyboard_event_source->on_key_down(p->vkCode);
			}
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP: {
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
			for (auto keyboard_event_source : _keyboard_hooks) {
				keyboard_event_source->on_key_up(p->vkCode);
			}
			break;
		}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}