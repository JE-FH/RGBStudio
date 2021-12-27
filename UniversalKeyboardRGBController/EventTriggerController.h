#pragma once
#include <vector>
#include <queue>
#include "EffectManager.h"
#include "Trigger.h"
#include "Event.h"
#include "IEventSource.h"
#include "EventQueue.h"
class EventTriggerController
{
public:
	EventTriggerController(EffectManager effect_manager);

	void add_event_source(std::unique_ptr<IEventSource> event_source);
	void add_trigger(std::unique_ptr<Trigger> trigger);
	void run();
private:
	EffectManager _effect_manager;
	std::vector<std::unique_ptr<Trigger>> _triggers;
	EventQueue _queued_events;
	std::vector<std::unique_ptr<IEventSource>> _event_sources;
};

