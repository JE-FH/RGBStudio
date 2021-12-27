#pragma once
#include "RGBColor.h"
class IKeyLight
{
public:
	/// <summary>
	/// x position in cm
	/// </summary>
	float x;
	/// <summary>
	/// y position in cm
	/// </summary>
	float y;

	/// <summary>
	/// device specific key code
	/// </summary>
	unsigned short code;

	virtual void set_color(const RGBColor& color) = 0;
	virtual void layer_color(const RGBColor& color, float opacity) = 0;
	virtual RGBColor get_color() = 0;

	virtual ~IKeyLight() {};
	
};

