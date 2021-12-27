#pragma once
#include "IEffectAction.h"
#include "Event.h"
#include <vector>
class Trigger {
public:
	virtual ~Trigger() {}
	virtual void handle_event(EffectManager& effect_manager, Event& ev) = 0;
	
	void run_actions(EffectManager& effect_manager) {
		for (auto& action : _actions) {
			action->do_effect(effect_manager);
		}
	}

	void add_action(std::shared_ptr<IEffectAction> action) {
		_actions.push_back(std::move(action));
	}
private:
	std::vector<std::shared_ptr<IEffectAction>> _actions;
};