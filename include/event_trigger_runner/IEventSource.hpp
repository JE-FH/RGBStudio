#pragma once
#include <queue>
#include "EventQueue.hpp"
class IEventSource {
public:
	virtual ~IEventSource() {}

	virtual void poll_events(EventQueue& event_queue) = 0;
};