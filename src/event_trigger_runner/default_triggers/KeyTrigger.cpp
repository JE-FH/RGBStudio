#include <event_trigger_runner/default_triggers/KeyTrigger.hpp>
#include <event_trigger_runner/KeyEvent.hpp>

KeyTrigger::KeyTrigger(std::string trigger_name, unsigned short trigger_key, bool trigger_on_press, bool trigger_on_release, bool trigger_on_repeat)
	: Trigger(trigger_name)
{
	_trigger_key = trigger_key;
	_trigger_on_press = trigger_on_press;
	_trigger_on_release = trigger_on_release;
	_trigger_on_repeat = trigger_on_repeat;
}

bool KeyTrigger::should_trigger(Event& ev)
{
	if (auto key_event = dynamic_cast<KeyEvent*>(&ev)) {
		if (key_event->os_specific_code != _trigger_key) {
			return false;
		}
		if (!key_event->pressed && (_trigger_on_release)) {
			return true;
		}

		if (key_event->repeated && key_event->pressed && _trigger_on_repeat) {
			return true;
		}

		if (!key_event->repeated && key_event->pressed && _trigger_on_press) {
			return true;
		}
	}
	return false;
}
