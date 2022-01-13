#pragma once
#include <cmath>
#include "RGBColor.hpp"
template<typename T>
concept Blender = requires(T t, float a, float b, float c)
{
	{ T::blend(a, b, c) } -> std::convertible_to<float>;
};

class NaturalBlend {
public:
	static float blend(float bg_value, float fg_value, float alpha) {
		return std::sqrt((1 - alpha) * std::pow(bg_value, 2) + alpha * std::pow(fg_value, 2));
	}
};

class LinearBlend {
public:
	static float blend(float bg_value, float fg_value, float alpha) {
		return (1 - alpha) * bg_value + alpha * fg_value;
	}
};

template <class T>
RGBColor blend_color(const RGBColor& bg, const RGBColor& fg, float alpha) {
	RGBColor blended_color;
	blended_color.r = T::blend(bg.r / 255.f, fg.r / 255.f, alpha) * 255;
	blended_color.g = T::blend(bg.g / 255.f, fg.g / 255.f, alpha) * 255;
	blended_color.b = T::blend(bg.b / 255.f, fg.b / 255.f, alpha) * 255;

	return blended_color;
}