#pragma once
#include "RGBColor.hpp"
class KeyLight
{
public:
	KeyLight(float x, float y, unsigned short code, RGBColor color);

	/// <summary>
	/// x position in cm
	/// </summary>
	const float x;
	/// <summary>
	/// y position in cm
	/// </summary>
	const float y;

	/// <summary>
	/// device specific key code, unique for every key
	/// </summary>
	const unsigned short code;

	RGBColor color;

	void blend_color(const RGBColor& color, float opacity);
};

