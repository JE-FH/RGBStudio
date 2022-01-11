#include <windows_event_sources/KeyboardEventSource.hpp>
#include <event_trigger_runner/KeyEvent.hpp>
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
	auto guard = std::lock_guard(queued_events_mutex);
	while (queued_events.size() > 0) {
		event_queue.push(std::move(queued_events.front()));
		queued_events.pop();
	}
}

void KeyboardEventSource::on_key_down(unsigned long code, unsigned char scancode)
{
	auto guard = std::lock_guard(queued_events_mutex);
	queued_events.push(std::make_unique<KeyEvent>(code, scancode, true, false));
}

void KeyboardEventSource::on_key_repeat(unsigned long code, unsigned char scancode)
{
	auto guard = std::lock_guard(queued_events_mutex);
	queued_events.push(std::make_unique<KeyEvent>(code, scancode, true, true));
}

void KeyboardEventSource::on_key_up(unsigned long code, unsigned char scancode)
{
	auto guard = std::lock_guard(queued_events_mutex);
	queued_events.push(std::make_unique<KeyEvent>(code, scancode, false, false));
}

void KeyboardEventSource::init()
{
	if (inited) {
		return;
	}
	event_loop_thread = std::thread(win32_event_loop);
}


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

void KeyboardEventSource::win32_event_loop()
{
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	printf("Event loop ended?\n");

	UnhookWindowsHookEx(hhkLowLevelKybd);
}



std::set<KeyboardEventSource*> KeyboardEventSource::_keyboard_hooks;
std::set<DWORD> KeyboardEventSource::pressed_keys;
bool KeyboardEventSource::inited;
std::thread KeyboardEventSource::event_loop_thread;
