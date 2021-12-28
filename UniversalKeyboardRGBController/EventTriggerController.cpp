#include "EventTriggerController.h"

EventTriggerController::EventTriggerController(EffectManager effect_manager)
	: _effect_manager(std::move(effect_manager))
{
}

void EventTriggerController::add_event_source(std::unique_ptr<IEventSource> event_source)
{
	_event_sources.push_back(std::move(event_source));
}

void EventTriggerController::add_trigger(std::unique_ptr<Trigger> trigger)
{
	_triggers.push_back(std::move(trigger));
}

void EventTriggerController::run()
{
	while (true) {
		for (const auto& event_source : _event_sources) {
			event_source->poll_events(_queued_events);
		}

		std::unique_ptr<Event> queued_event;
		while ((queued_event = _queued_events.pop()) != nullptr) {
			//printf("%s\n", queued_event->describe().c_str());
			for (auto& trigger : _triggers) {
				trigger->handle_event(_effect_manager, *queued_event);
			}
		}

		_effect_manager.tick();
	}
}
