#include <event_trigger_runner/EventManager.hpp>

EventManager::EventManager() {
	
}

void EventManager::add_event_source(std::shared_ptr<IEventSource> event_source) {
	_event_sources.push_back(std::move(event_source));
}

void EventManager::poll_events() {
	for (const auto& event_source : _event_sources) {
		event_source->poll_events(_queued_events);
	}
}

std::unique_ptr<Event> EventManager::pop_event()
{
	return _queued_events.pop();
}
