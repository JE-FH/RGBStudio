#include <event_trigger_runner/TriggerObserverDispatcher.hpp>
#include <iostream>

TriggerObserverDispatcher::TriggerObserverDispatcher() {}

TriggerObserverDispatcher::~TriggerObserverDispatcher() {
	for (auto iter = _observers.begin(); iter != _observers.end();) {
		iter->second->_creator = nullptr;
	}
}

void TriggerObserverDispatcher::add_observer(std::string trigger, TriggerObserver& observer) {
	std::cout << "added observer for: " << trigger << std::endl;
	observer._creator = this;
	_observers.insert(std::pair(std::move(trigger), &observer));
}

void TriggerObserverDispatcher::remove_observer(TriggerObserver* observer) {
	for (auto iter = _observers.begin(); iter != _observers.end();) {
		if (iter->second == observer) {
			iter = _observers.erase(iter);
		}
		else {
			++iter;
		}
	}
	observer->_creator = nullptr;
}

void TriggerObserverDispatcher::dispatch(const std::string& trigger) {
	std::cout << "dispatching to observers for: " << trigger << std::endl;
	auto trigger_range = _observers.equal_range(trigger);
	for (auto iter = trigger_range.first; iter != trigger_range.second; iter++) {
		iter->second->Trigger(trigger);
	}
}
