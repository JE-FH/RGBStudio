#pragma once
#include <string>

class IConfigValueTypeDesc {
	virtual std::string get_friendly_name() = 0;
};

template<typename T>
concept ConfigValueTypeDesc = requires(T a) {
	{T::friendly_name()} -> std::same_as<std::string>;
	std::derived_from<T, IConfigValueTypeDesc>;
};
