#include <dynamic_config/DynamicConfig.hpp>

ConfigValueException::ConfigValueException(std::string key, std::string expected_friendly_type_name) {
	this->key = std::move(key);
	this->expected_friendly_type_name = std::move(expected_friendly_type_name);
	this->error_message = "error with " + this->key + ": " + this->expected_friendly_type_name;
}

const char* ConfigValueException::what() const throw() {
	return error_message.c_str();
}

MissingConfigValueExecption::MissingConfigValueExecption(std::string key, std::string expected_friendly_type_name)
	: ConfigValueException(std::move(key), std::move(expected_friendly_type_name)) 
{
	error_message = 
		"Missing config value "
		"\"" + this->key + "\""
		" with expected type "
		"\"" + this->expected_friendly_type_name + "\"";
}

ConfigValueWrongTypeExecption::ConfigValueWrongTypeExecption(std::string key, 
	std::string expected_friendly_type_name,
	std::string actual_value
)
	: ConfigValueException(std::move(key), std::move(expected_friendly_type_name))
{
	this->actual_value = std::move(actual_value);
	error_message =
		"Expected config value "
		"\"" + this->key + "\""
		" to have type "
		"\"" + this->expected_friendly_type_name + "\""
		" but got type "
		"\"" + this->actual_value + "\"";
		
}


const IConfigValue* DynamicConfig::get_config_value(const std::string& key) const {
	auto value = config_values.find(key);
	if (value == config_values.end()) {
		return nullptr;
	} else {
		return value->second.get();
	}
}

void DynamicConfig::set_config_value(const std::string& key, std::unique_ptr<IConfigValue> value) {
	config_values.insert(std::pair(key, std::move(value)));
}
