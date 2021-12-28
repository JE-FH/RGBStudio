#include "KeyboardEventSource.h"
#include "KeyEvent.h"
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

void KeyboardEventSource::on_key_down(unsigned long code, unsigned char scancode)
{
	queued_events.push(std::make_unique<KeyEvent>(code, scancode, true, false));
}

void KeyboardEventSource::on_key_repeat(unsigned long code, unsigned char scancode)
{
	queued_events.push(std::make_unique<KeyEvent>(code, scancode, true, true));
}

void KeyboardEventSource::on_key_up(unsigned long code, unsigned char scancode)
{
	queued_events.push(std::make_unique<KeyEvent>(code, scancode, false, false));
}

void KeyboardEventSource::init()
{
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
	
}

std::set<KeyboardEventSource*> KeyboardEventSource::_keyboard_hooks;
std::set<DWORD> KeyboardEventSource::pressed_keys;

LRESULT KeyboardEventSource::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN: {
				PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
				bool is_repeat = pressed_keys.contains(p->vkCode);

				for (auto keyboard_event_source : _keyboard_hooks) {
					if (is_repeat) {
						keyboard_event_source->on_key_repeat(p->vkCode, p->scanCode);
					}
					else {
						keyboard_event_source->on_key_down(p->vkCode, p->scanCode);
					}
				}
				if (!is_repeat) {
					pressed_keys.insert(p->vkCode);
				}
				break;
			}
			case WM_KEYUP:
			case WM_SYSKEYUP: {
				PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
				pressed_keys.erase(p->vkCode);
				for (auto keyboard_event_source : _keyboard_hooks) {
					keyboard_event_source->on_key_up(p->vkCode, p->scanCode);
				}
				break;
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}