#pragma once
class TriggerObserverDispatcher;
#include "TriggerObserverDispatcher.h"
#include <string>

class TriggerObserver {
public:
	TriggerObserver(const TriggerObserver&) = delete;
	TriggerObserver(TriggerObserver&&) = delete;

	TriggerObserver();

	virtual ~TriggerObserver();

	virtual void Trigger(std::string trigger_name) = 0;
private:
	TriggerObserverDispatcher* _creator;
	friend TriggerObserverDispatcher;
};