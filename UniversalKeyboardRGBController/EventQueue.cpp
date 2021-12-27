#include "EventQueue.h"

EventQueue::EventQueue()
{

}

std::unique_ptr<Event> EventQueue::pop()
{
	if (_queued_events.size() > 0) {
		std::unique_ptr<Event> rv = std::move(_queued_events.front());
		_queued_events.pop();
		return std::move(rv);
	}
	return std::unique_ptr<Event>(nullptr);
}

void EventQueue::push(std::unique_ptr<Event> ev)
{
	_queued_events.push(std::move(ev));
}
