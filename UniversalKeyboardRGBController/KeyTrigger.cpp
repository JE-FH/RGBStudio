#include "KeyTrigger.h"
#include "KeyEvent.h"

KeyTrigger::KeyTrigger(unsigned short trigger_key, bool trigger_on_press, bool trigger_on_release, bool trigger_on_repeat)
{
	_trigger_key = trigger_key;
	_trigger_on_press = trigger_on_press;
	_trigger_on_release = trigger_on_release;
	_trigger_on_repeat = trigger_on_repeat;
}

void KeyTrigger::handle_event(EffectManager& effect_manager, Event& ev)
{
	if (auto key_event = dynamic_cast<KeyEvent*>(&ev)) {
		if (!key_event->pressed && (_trigger_on_release)) {
			run_actions(effect_manager);
			return;
		}

		if (key_event->repeated && key_event->pressed && _trigger_on_repeat) {
			run_actions(effect_manager);
			return;
		}

		if (!key_event->repeated && key_event->pressed && _trigger_on_press) {
			run_actions(effect_manager);
			return;
		}
	}
}
