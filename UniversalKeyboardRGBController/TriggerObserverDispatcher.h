#pragma once
class TriggerObserver;
#include "TriggerObserver.h"
#include <vector>
#include <map>
#include <string>
#include <algorithm>

class TriggerObserverDispatcher
{
public:
	TriggerObserverDispatcher(const TriggerObserverDispatcher&) = delete;
	TriggerObserverDispatcher(TriggerObserverDispatcher&&) = delete;
	TriggerObserverDispatcher();
	~TriggerObserverDispatcher();

	void add_observer(std::string trigger, TriggerObserver& observer);
	void remove_observer(TriggerObserver* observer);
	void dispatch(const std::string& trigger);
private:
	std::multimap<std::string, TriggerObserver*> _observers;
};

