#include <event_trigger_runner/TriggerObserver.hpp>

TriggerObserver::TriggerObserver() {
	_creator = nullptr;
}

TriggerObserver::~TriggerObserver() {
	if (_creator != nullptr) {
		_creator->remove_observer(this);
	}
}
