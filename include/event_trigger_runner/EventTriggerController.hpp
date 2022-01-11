#pragma once
#include <effect_manager/EffectManager.hpp>
#include "Trigger.hpp"
#include "Event.hpp"
#include "IEventSource.hpp"
#include "EventQueue.hpp"
#include "IEffectFactory.hpp"
#include "EventManager.hpp"
#include "TriggerObserverDispatcher.hpp"
#include <vector>
#include <queue>
#include <map>
class EventTriggerController
{
public:
	EventTriggerController(EffectManager effect_manager, EventManager event_manager);

	void add_action_trigger(std::string trigger_name, std::string factory_name);
	void add_trigger(std::unique_ptr<Trigger> trigger);
	void add_effect_factory(std::string factory_name, std::unique_ptr<IEffectFactory> effect_factory);
	void run();
private:
	EventManager _event_manager;
	EffectManager _effect_manager;
	TriggerObserverDispatcher _trigger_observer_dispatcher;
	std::vector<std::unique_ptr<Trigger>> _triggers;
	std::multimap<std::string, std::string> _action_triggers;
	std::map<std::string, std::unique_ptr<IEffectFactory>> _effect_factories;
};

