#include <event_trigger_runner/EventTriggerController.hpp>
#include <vector>

EventTriggerController::EventTriggerController(EffectManager effect_manager, EventManager event_manager)
	: _effect_manager(std::move(effect_manager)), _event_manager(std::move(event_manager))
{
}

void EventTriggerController::add_action_trigger(std::string trigger_name, std::string factory_name)
{
	_action_triggers.insert(std::pair(std::move(trigger_name), std::move(factory_name)));
}

void EventTriggerController::add_trigger(std::unique_ptr<Trigger> trigger)
{
	_triggers.push_back(std::move(trigger));
}

void EventTriggerController::add_effect_factory(std::string factory_name, std::unique_ptr<IEffectFactory> effect_factory)
{
	_effect_factories.insert(std::pair(std::move(factory_name), std::move(effect_factory)));
}

void EventTriggerController::run()
{
	while (true) {
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

			auto action_trigger_range = _action_triggers.equal_range(triggered_action_name);
			for (auto action_trigger = action_trigger_range.first; action_trigger != action_trigger_range.second; action_trigger++) {
				_trigger_observer_dispatcher.dispatch(action_trigger->second);
				auto effect_factory = _effect_factories.find(action_trigger->second);
				if (effect_factory != _effect_factories.end()) {
					effect_factory->second->add_new_instance(_effect_manager, _trigger_observer_dispatcher);
				}
			}
		}

		_effect_manager.tick();
	}
}
