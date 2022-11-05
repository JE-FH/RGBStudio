#pragma once
#include <effect_manager/EffectManager.hpp>
#include "Trigger.hpp"
#include "Event.hpp"
#include "IEventSource.hpp"
#include "EventQueue.hpp"
#include "IEffect.hpp"
#include "EventManager.hpp"
#include "TriggerObserverDispatcher.hpp"
#include <vector>
#include <queue>
#include <map>
class EventTriggerController
{
public:
	EventTriggerController(EffectManager effect_manager, EventManager event_manager);

	void add_trigger(std::unique_ptr<Trigger> trigger);
	void add_trigger_action_edge(std::string trigger_name, std::string action_name);
	void add_action_effect_edge(std::string action_name, std::string effect_name);
	void add_effect(std::string effect_name, std::unique_ptr<IEffect> effect);
	void clear();
	void run_tick();
	void run();
private:
	EventManager _event_manager;
	EffectManager _effect_manager;
	TriggerObserverDispatcher _trigger_observer_dispatcher;

	std::vector<std::unique_ptr<Trigger>> _triggers;
	
	std::multimap<std::string, std::string> _trigger_action_edges;
	std::multimap<std::string, std::string> _action_effect_edges;

	std::map<std::string, std::unique_ptr<IEffect>> _effects;
};

