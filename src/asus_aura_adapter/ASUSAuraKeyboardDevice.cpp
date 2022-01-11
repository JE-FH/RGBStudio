//Since the great comitee has deprecated this without giving an alternative, we just rely on the deprecation
//When they have gotten the finger out of their collective ass, and provide an alternative, this needs
//to be redone
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <asus_aura_adapter/ASUSAuraKeyboardDevice.hpp>
#include <asus_aura_adapter/ASUSAuraKeyLight.hpp>
#include <effect_manager/ColorUtils.hpp>
#include <exception>
#include <stdexcept>
#include <locale>
#include <codecvt>

ASUSAuraKeyboardDevice::ASUSAuraKeyboardDevice(AuraServiceLib::IAuraSyncKeyboardPtr native_dev)
{
	if (native_dev == nullptr) {
		throw std::invalid_argument("native_dev cannot be null");
	}
	_native_dev = native_dev;
	auto lights = _native_dev->GetKeys();

	/* We want to make sure that the array does not move around
	 * This is so the pointers in _key_lights_raw_list do not
	 * get invalidated.
	 * This could have been avoided by having each light in a pointer.
	 * However this would lead to alot of unnessesary pointer hunting when
	 * clearing the lights
	 */
	_key_lights.reserve(lights->Count);

	for (int i = 0; i < lights->Count; i++) {
		auto new_light = ASUSAuraKeyLight(lights->Item[i]);
		_key_lights.push_back(std::move(new_light));
		_key_lights_raw_list.push_back(&_key_lights.at(_key_lights.size() - 1));
	}
	actual_width = 0;
	for (const auto& light : _key_lights) {
		if (light.x + 1 > actual_width) {
			actual_width = light.x + 1;
		}
	}
}

ASUSAuraKeyboardDevice::~ASUSAuraKeyboardDevice()
{
}

std::string ASUSAuraKeyboardDevice::get_name()
{
	auto bstr_name = _native_dev->Name.GetBSTR();
	auto u16_name = std::u16string(bstr_name, bstr_name + _native_dev->Name.length());

	std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> utf16_to_utf8_conv;

	return utf16_to_utf8_conv.to_bytes(u16_name);
}

void ASUSAuraKeyboardDevice::apply_colors()
{
	HRESULT hr = _native_dev->Apply();
	if (!SUCCEEDED(hr)) {
		throw new std::exception("Could not apply colors to keyboard");
	}
}

IKeyLight** ASUSAuraKeyboardDevice::key_begin()
{
	return _key_lights_raw_list.begin()._Ptr;
}

IKeyLight** ASUSAuraKeyboardDevice::key_end()
{
	return _key_lights_raw_list.end()._Ptr;
}

float ASUSAuraKeyboardDevice::get_width()
{
	return actual_width;
	//return _native_dev->Width;
}

float ASUSAuraKeyboardDevice::get_height()
{
	return _native_dev->Height;
}

void ASUSAuraKeyboardDevice::fill(const RGBColor& color)
{
	for (ASUSAuraKeyLight& light : _key_lights) {
		light.set_color(color);
	}
}

void ASUSAuraKeyboardDevice::fill(const RGBColor& color, float alpha)
{
	for (ASUSAuraKeyLight& light : _key_lights) {
		light.set_color(blend_color<LinearBlend>(light.get_color(), color, alpha));
	}
}
