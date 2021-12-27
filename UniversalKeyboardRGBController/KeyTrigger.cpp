#include "KeyTrigger.h"
#include "KeyPressEvent.h"

KeyTrigger::KeyTrigger(unsigned short trigger_key)
{
	_trigger_key = trigger_key;
}

void KeyTrigger::handle_event(EffectManager& effect_manager, Event& ev)
{
	if (KeyPressEvent* key_press_event = dynamic_cast<KeyPressEvent*>(&ev)) {
		if (key_press_event->os_specific_code) {
			run_actions(effect_manager);
		}
	}
}
