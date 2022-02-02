#pragma once
#include <string>

class IConfigValueTypeDesc {
public:
	virtual ~IConfigValueTypeDesc() {}
	virtual std::string get_friendly_name() const = 0;
	virtual std::string get_internal_name() const = 0;
};

template<typename T>
concept ConfigValueTypeDesc = requires(T a) {
	{T::friendly_name()} -> std::same_as<std::string>;
	std::derived_from<T, IConfigValueTypeDesc>;
};
