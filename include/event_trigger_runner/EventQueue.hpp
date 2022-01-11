#pragma once
#include <queue>
#include <memory>
#include "Event.hpp"
class EventQueue
{
public:
	EventQueue();

	std::unique_ptr<Event> pop();
	void push(std::unique_ptr<Event> ev);

	std::queue<std::unique_ptr<Event>> _queued_events;
};

