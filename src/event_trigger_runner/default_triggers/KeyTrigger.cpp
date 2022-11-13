#include <event_trigger_runner/default_triggers/KeyTrigger.hpp>
#include <event_trigger_runner/KeyEvent.hpp>

KeyTrigger::KeyTrigger(std::string trigger_name, unsigned short trigger_key)
	: Trigger(trigger_name)
{
	_trigger_key = trigger_key;
}

bool KeyTrigger::should_trigger(Event& ev, std::string& trigger_sub_name)
{
	if (auto key_event = dynamic_cast<KeyEvent*>(&ev)) {
		if (key_event->os_specific_code != _trigger_key) {
			return false;
		}

		if (key_event->pressed) {
			trigger_sub_name = "pressed";
			return true;
		}

		if (key_event->repeated && key_event->pressed) {
			trigger_sub_name = "repeated";
			return true;
		}

		if (!key_event->pressed) {
			trigger_sub_name = "released";
			return true;
		}
	}
	return false;
}
