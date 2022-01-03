#pragma once
#include <chrono>
#include <string>
class Event {
public:
	Event() : created_at(std::chrono::system_clock::now()) {}

	virtual ~Event() {}
	
	virtual std::string describe() = 0;

	const std::chrono::system_clock::time_point created_at;
};