#include <dynamic_config/ConfigGenericValue.hpp>

namespace ConfigGenericValueConverter {
	std::string to_string(std::string t) {
		return t;
	}

	std::string to_string(const RGBColor& rgbcolor) {
		return "rgb(" + to_string(rgbcolor.r) + ", " + to_string(rgbcolor.g) + ", " + to_string(rgbcolor.b) + ")";
	}
}

std::string ConfigStringTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigStringTypeDesc::friendly_name() {
	return "string";
}

std::unique_ptr<IConfigValue> ConfigStringTypeDesc::decode(const std::string& value) const {
	return std::make_unique<ConfigStringValue>(value);
}

std::string ConfigStringTypeDesc::get_internal_name() const {
	return "String";
}

std::string ConfigIntegerTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigIntegerTypeDesc::friendly_name() {
	return "integer";
}

std::string ConfigIntegerTypeDesc::get_internal_name() const {
	return "Integer";
}

std::unique_ptr<IConfigValue> ConfigIntegerTypeDesc::decode(const std::string& value) const {
	return std::make_unique<ConfigIntegerValue>(std::stoll(value));
}

std::string ConfigNumberTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigNumberTypeDesc::friendly_name() {
	return "number";
}

std::string ConfigNumberTypeDesc::get_internal_name() const {
	return "Number";
}

std::unique_ptr<IConfigValue> ConfigNumberTypeDesc::decode(const std::string& value) const {
	return std::make_unique<ConfigNumberValue>(std::stod(value));
}

std::string ConfigRGBColorTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigRGBColorTypeDesc::friendly_name() {
	return "rgb color";
}

std::string ConfigRGBColorTypeDesc::get_internal_name() const {
	return "RGBColor";
}

unsigned char decodeHexNibble(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a';
	if (c >= 'A' && c <= 'F')
		return c - 'A';
	throw std::exception("Invalid hex character");
}

unsigned char decodeHexByte(char c1, char c2) {
	return (decodeHexNibble(c1) << 4) + decodeHexNibble(c2);
}

std::unique_ptr<IConfigValue> ConfigRGBColorTypeDesc::decode(const std::string& value) const {
	if (value.size() != 6) {
		throw std::exception("Invalid color value");
	}

	for (size_t i = 0; i < 6; i++) {
		if (!(
			(value[i] >= '0' && value[i] <= '9') ||
			(value[i] >= 'a' && value[i] <= 'f') ||
			(value[i] >= 'A' && value[i] <= 'F')
		)) {
			throw std::exception("Invalid color value");
		}
	}

	return std::make_unique<ConfigRGBColorValue>(RGBColor{
		.r = decodeHexByte(value[0], value[1]),
		.g = decodeHexByte(value[2], value[3]),
		.b = decodeHexByte(value[4], value[5])
	});
}

std::string ConfigBoolTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigBoolTypeDesc::get_internal_name() const {
	return "Bool";
}

std::string ConfigBoolTypeDesc::friendly_name() {
	return "bool";
}

std::unique_ptr<IConfigValue> ConfigBoolTypeDesc::decode(const std::string& value) const {
	if (value == "true") {
		return std::make_unique<ConfigBoolValue>(true);
	}
	else if (value == "false") {
		return std::make_unique<ConfigBoolValue>(false);
	}
	else {
		throw std::exception("Invalid bool value");
	}
}

std::string ConfigActionNameTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigActionNameTypeDesc::get_internal_name() const {
	return "Action";
}

std::string ConfigActionNameTypeDesc::friendly_name() {
	return "action";
}

std::unique_ptr<IConfigValue> ConfigActionNameTypeDesc::decode(const std::string& value) const {
	return std::make_unique<ConfigActionNameValue>(value);
}
