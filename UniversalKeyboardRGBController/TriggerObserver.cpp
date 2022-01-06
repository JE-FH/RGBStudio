#include "TriggerObserver.h"

TriggerObserver::TriggerObserver() {
	_creator = nullptr;
}

TriggerObserver::~TriggerObserver() {
	if (_creator != nullptr) {
		_creator->remove_observer(this);
	}
}
