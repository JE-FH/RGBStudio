#pragma once
#include <string>
#include "KeyLight.hpp"
#include "RGBColor.hpp"
class IKeyboardDevice {
public:
	virtual ~IKeyboardDevice() {}

	virtual std::string get_name() = 0;

	/// <summary>
	/// Applies the set key colors
	/// </summary>
	virtual void apply_colors() = 0;
	
	virtual KeyLight* key_begin() = 0;
	virtual KeyLight* key_end() = 0;

	virtual float get_width() = 0;
	virtual float get_height() = 0;
};