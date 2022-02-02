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


std::string ConfigNumberTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigNumberTypeDesc::friendly_name() {
	return "number";
}

std::string ConfigNumberTypeDesc::get_internal_name() const {
	return "Number";
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

std::string ConfigBoolTypeDesc::get_friendly_name() const {
	return friendly_name();
}

std::string ConfigBoolTypeDesc::get_internal_name() const {
	return "Bool";
}

std::string ConfigBoolTypeDesc::friendly_name() {
	return "bool";
}