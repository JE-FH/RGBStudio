#pragma once
#include <vector>
#include <queue>
#include "EffectManager.h"
#include "Trigger.h"
#include "Event.h"
#include "IEventSource.h"
#include "EventQueue.h"
#include "IEffectFactory.h"
#include "ActionTrigger.h"
#include <map>
class EventTriggerController
{
public:
	EventTriggerController(EffectManager effect_manager);

	void add_event_source(std::unique_ptr<IEventSource> event_source);
	void add_action_trigger(std::string trigger_name, std::string factory_name);
	void add_trigger(std::unique_ptr<Trigger> trigger);
	void add_effect_factory(std::string factory_name, std::unique_ptr<IEffectFactory> effect_factory);
	void run();
private:
	EffectManager _effect_manager;
	std::vector<std::unique_ptr<Trigger>> _triggers;
	std::multimap<std::string, std::string> _action_triggers;
	std::map<std::string, std::unique_ptr<IEffectFactory>> _effect_factories;
	EventQueue _queued_events;
	std::vector<std::unique_ptr<IEventSource>> _event_sources;
};

