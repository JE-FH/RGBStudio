#pragma once
#include "EventQueue.hpp"
#include "IEventSource.hpp"
#include <vector>
#include <memory>

class EventManager {
public:
	EventManager();
	void add_event_source(std::unique_ptr<IEventSource> event_source);
	void poll_events();
	std::unique_ptr<Event> pop_event();
private:
	EventQueue _queued_events;
	std::vector<std::unique_ptr<IEventSource>> _event_sources;
};

