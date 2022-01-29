#pragma once
#include <string>

class IConfigValue {
public:
	virtual ~IConfigValue() {}

	virtual std::string to_string() const = 0;
};

template<typename T>
concept ConfigValue = requires(T a) {
	std::derived_from<T, IConfigValue>;
};
