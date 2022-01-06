#pragma once
#include "IKeyLight.h"
#import "libid:F1AA5209-5217-4B82-BA7E-A68198999AFA"
class ASUSAuraKeyLight : public IKeyLight {
public:
	ASUSAuraKeyLight(AuraServiceLib::IAuraRgbKeyPtr native_key);
	ASUSAuraKeyLight(ASUSAuraKeyLight&) = delete;
	ASUSAuraKeyLight(ASUSAuraKeyLight&& other);
	// Inherited via IKeyLight
	virtual void set_color(const RGBColor& color) override;
	virtual void set_color(const RGBColor& color, float opacity) override;
	virtual RGBColor get_color() override;
private:
	AuraServiceLib::IAuraRgbKeyPtr _native_key;
};