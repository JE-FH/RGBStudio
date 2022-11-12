#include <event_trigger_runner/EventTriggerController.hpp>
#include <vector>
#include <iostream>

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
	_effect_manager.clear();
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
	std::vector<std::string> triggered_triggers_names;
	while ((queued_event = _event_manager.pop_event()) != nullptr) {
		for (auto& trigger : _triggers) {
			if (trigger->should_trigger(*queued_event)) {
				triggered_triggers_names.push_back(trigger->trigger_name);
			}
		}
	}

	for (const auto& triggered_trigger_name : triggered_triggers_names) {
		auto action_range = _trigger_action_edges.equal_range(triggered_trigger_name);
		std::cout << "trigger: " << triggered_trigger_name << std::endl;
		for (auto action_it = action_range.first; action_it != action_range.second; action_it++) {
			std::cout << "edge: " << action_it->first << " -> " << action_it->second << std::endl;

			auto effect_range = _action_effect_edges.equal_range(action_it->second);
			_trigger_observer_dispatcher.dispatch(action_it->second);

			for (auto effect_it = effect_range.first; effect_it != effect_range.second; effect_it++) {
				std::cout << "edge: " << effect_it->first << " -> " << effect_it->second << std::endl;
				auto effect_factory = _effects.find(effect_it->second);

				if (effect_factory != _effects.end()) {
					std::cout << "effect: " << effect_factory->first << std::endl;

					effect_factory->second->add_new_instance(_effect_manager, _trigger_observer_dispatcher);
				}
			}
		}
	}

	_effect_manager.tick();
}