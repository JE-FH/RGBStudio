#include "ASUSAuraKeyLight.h"

ASUSAuraKeyLight::ASUSAuraKeyLight(AuraServiceLib::IAuraRgbKeyPtr native_key)
{
	_native_key = native_key;
	this->code = _native_key->GetCode();
	//It is unclear in the documentation whether this is the position in the 
	//Column/rows of the keyboard or if its the physical position
	this->x = _native_key->GetX();
	this->y = _native_key->GetY();
}

ASUSAuraKeyLight::ASUSAuraKeyLight(ASUSAuraKeyLight&& other)
{
	this->_native_key = std::move(other._native_key);
	this->code = std::move(other.code);
	this->x = std::move(other.x);
	this->y = std::move(other.y);
}

void ASUSAuraKeyLight::set_color(const RGBColor& color)
{
	_native_key->Red = color.r;
	_native_key->Green = color.g;
	_native_key->Blue = color.b;
}

RGBColor ASUSAuraKeyLight::get_color()
{
	return RGBColor{ _native_key->Red, _native_key->Green, _native_key->Blue };
}
