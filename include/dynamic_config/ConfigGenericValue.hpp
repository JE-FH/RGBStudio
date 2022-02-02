#pragma once
#include "IConfigValue.hpp"
#include "IConfigValueTypeDesc.hpp"
#include <device_adapter_loader/RGBColor.hpp>

namespace ConfigGenericValueConverter {
	namespace adl_helper {
		template<class T>
		std::string as_string(T&& t) {
			using std::to_string;
			return to_string(std::forward<T>(t));
		}
	}
	template<class T>
	std::string to_string(T&& t) {
		return adl_helper::as_string(std::forward<T>(t));
	}

	std::string to_string(std::string t);
	std::string to_string(const RGBColor& rgbcolor);
}

template<typename T, ConfigValueTypeDesc _TTypeDesc>
class ConfigGenericValue : public IConfigValue {
private:
	T value;
public:
	ConfigGenericValue(T value) : value(std::move(value)) {}

	const T& get_value() const {
		return value;
	}

	std::string to_string() const override {
		return ConfigGenericValueConverter::to_string(value);
	}

	using TTypeDesc = _TTypeDesc;
};

class ConfigStringTypeDesc : public IConfigValueTypeDesc {
public:
	ConfigStringTypeDesc() {}

	std::string get_friendly_name() const override;
	std::string get_internal_name() const override;

	static std::string friendly_name();
};
using ConfigStringValue = ConfigGenericValue<std::string, ConfigStringTypeDesc>;


class ConfigIntegerTypeDesc : public IConfigValueTypeDesc {
public:
	ConfigIntegerTypeDesc() {}
	
	std::string get_friendly_name() const override;
	std::string get_internal_name() const override;

	static std::string friendly_name();
};
using ConfigIntegerValue = ConfigGenericValue<long long, ConfigIntegerTypeDesc>;

class ConfigNumberTypeDesc : public IConfigValueTypeDesc {
public:
	ConfigNumberTypeDesc() {}

	std::string get_friendly_name() const override;
	std::string get_internal_name() const override;

	static std::string friendly_name();
};
using ConfigNumberValue = ConfigGenericValue<double, ConfigNumberTypeDesc>;

class ConfigRGBColorTypeDesc : public IConfigValueTypeDesc {
public:
	ConfigRGBColorTypeDesc() {}

	std::string get_friendly_name() const override;
	std::string get_internal_name() const override;

	static std::string friendly_name();
	friend std::string ConfigGenericValueConverter::to_string(const RGBColor& rgbcolor);
};
using ConfigRGBColorValue = ConfigGenericValue<RGBColor, ConfigRGBColorTypeDesc>;


class ConfigBoolTypeDesc : public IConfigValueTypeDesc {
public:
	ConfigBoolTypeDesc() {}

	std::string get_friendly_name() const override;
	std::string get_internal_name() const override;

	static std::string friendly_name();
};
using ConfigBoolValue = ConfigGenericValue<bool, ConfigBoolTypeDesc>;
