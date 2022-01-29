#pragma once
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include "IConfigValue.hpp"
#include "IConfigValueTypeDesc.hpp"

class ConfigValueException : std::exception {
public:
	std::string key;
	std::string expected_friendly_type_name;
	std::string error_message;
	ConfigValueException(std::string key, std::string expected_friendly_type_name);

	const char* what() const throw();
};

class MissingConfigValueExecption : ConfigValueException {
public:
	MissingConfigValueExecption(std::string key, std::string expected_friendly_type_name);
};

class ConfigValueWrongTypeExecption : ConfigValueException {
public:
	std::string actual_value;
	ConfigValueWrongTypeExecption(std::string key, 
		std::string expected_friendly_type_name,
		std::string actual_value
	);
};


class DynamicConfig {
private:
	std::map<std::string, std::unique_ptr<IConfigValue>> config_values;
public:
	const IConfigValue* get_config_value(const std::string& key) const;
	template<ConfigValue T>
	const T& get_config_value(const std::string& key) const {
		const T* rv = get_optional_value<T>(key);
		if (rv == nullptr) {
			throw MissingConfigValueExecption(key, T::TTypeDesc::friendly_name());
		}

		return *rv;
	}

	template<ConfigValue T>
	const T* get_optional_value(const std::string& key) const {
		const IConfigValue* rv = get_config_value(key);
		if (rv == nullptr) {
			return nullptr;
		}

		if (const T* typed_rv = dynamic_cast<const T*>(rv)) {
			return typed_rv;
		} else {
			throw ConfigValueWrongTypeExecption(key, T::TTypeDesc::friendly_name(), rv->to_string());
		}
	}

	void set_config_value(const std::string& key, std::unique_ptr<IConfigValue> value);
};