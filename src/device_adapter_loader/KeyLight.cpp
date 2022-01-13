#include <device_adapter_loader/KeyLight.hpp>
#include <device_adapter_loader/ColorUtils.hpp>

KeyLight::KeyLight(float x, float y, unsigned short code, RGBColor color)
	: x(x), y(y), code(code), color(color) 
{}

void KeyLight::blend_color(const RGBColor& color, float opacity) {
	this->color = ::blend_color<LinearBlend>(this->color, color, opacity);
}