//Since the great comitee has deprecated this without giving an alternative, we just rely on the deprecation
//When they have gotten the finger out of their collective ass, and provide an alternative, this needs
//to be redone
#include "ASUSAuraKeyboardDevice.hpp"
#include <device_adapter_loader/ColorUtils.hpp>

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
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

	for (int i = 0; i < lights->Count; i++) {
		key_translation.insert(std::pair(lights->Item[i]->Code, lights->Item[i]));
		auto new_light = KeyLight(
			(float)lights->Item[i]->X,
			(float)lights->Item[i]->Y,
			lights->Item[i]->Code,
			RGBColor{
				lights->Item[i]->Red,
				lights->Item[i]->Green,
				lights->Item[i]->Blue,
			}
		);
		_raster.push_back(std::move(new_light));
	}
	actual_width = 0;
	for (const auto& light : _raster) {
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
	for (const auto& key : _raster) {
		auto translated_key = key_translation.find(key.code);
		if (translated_key != key_translation.end()) {
			translated_key->second->Red = key.color.r;
			translated_key->second->Green = key.color.g;
			translated_key->second->Blue = key.color.b;
		} else {
			throw std::runtime_error("Asus Aura adapter error, unknown key in list");
		}
	}

	HRESULT hr = _native_dev->Apply();
	if (!SUCCEEDED(hr)) {
		throw std::runtime_error("Could not apply colors to keyboard");
	}
}

KeyLight* ASUSAuraKeyboardDevice::key_begin()
{
	return _raster.begin()._Ptr;
}

KeyLight* ASUSAuraKeyboardDevice::key_end()
{
	return _raster.end()._Ptr;
}

float ASUSAuraKeyboardDevice::get_width()
{
	return actual_width;
}

float ASUSAuraKeyboardDevice::get_height()
{
	return _native_dev->Height;
}