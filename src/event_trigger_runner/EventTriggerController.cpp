#include <event_trigger_runner/EventTriggerController.hpp>
#include <vector>

EventTriggerController::EventTriggerController(EffectManager effect_manager, EventManager event_manager)
	: _effect_manager(std::move(effect_manager)), _event_manager(std::move(event_manager))
{
}

void EventTriggerController::add_trigger_action_edge(std::string trigger_name, std::string action_name)
{
	_trigger_action_edges.insert(std::pair(std::move(trigger_name), std::move(action_name)));
}

void EventTriggerController::add_action_effect_edge(std::string action_name, std::string effect_name) {
	_action_effect_edges.insert(std::pair(std::move(action_name), std::move(effect_name)));
}

void EventTriggerController::add_trigger(std::unique_ptr<Trigger> trigger)
{
	_triggers.push_back(std::move(trigger));
}

void EventTriggerController::add_effect(std::string effect_name, std::unique_ptr<IEffect> effect_factory)
{
	_effects.insert(std::pair(std::move(effect_name), std::move(effect_factory)));
}

void EventTriggerController::clear() {
	_triggers.clear();
	_trigger_action_edges.clear();
	_action_effect_edges.clear();
	_effects.clear();
	//TODO: Clear effectmanager
}

void EventTriggerController::run()
{
	while (true) {
		run_tick();
	}
}


void EventTriggerController::run_tick() 
{
	_event_manager.poll_events();

	std::unique_ptr<Event> queued_event;
	std::vector<std::string> triggered_action_names;
	while ((queued_event = _event_manager.pop_event()) != nullptr) {
		for (auto& trigger : _triggers) {
			if (trigger->should_trigger(*queued_event)) {
				triggered_action_names.push_back(trigger->trigger_name);
			}
		}
	}

	for (const auto& triggered_action_name : triggered_action_names) {
		auto effect_range = _action_effect_edges.equal_range(triggered_action_name);
		for (auto it = effect_range.first; it != effect_range.second; it++) {
			_trigger_observer_dispatcher.dispatch(it->second);

			auto effect_factory = _effects.find(it->second);
			if (effect_factory != _effects.end()) {
				effect_factory->second->add_new_instance(_effect_manager, _trigger_observer_dispatcher);
			}
		}
	}

	_effect_manager.tick();
}