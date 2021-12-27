#pragma once
#include <string>
class Event {
public:
	virtual ~Event() {}

	virtual std::string describe() = 0;
};