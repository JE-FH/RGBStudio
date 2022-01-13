#pragma once

#include <Windows.h>
#import "libid:F1AA5209-5217-4B82-BA7E-A68198999AFA"
#include <effect_manager/IKeyboardDevice.hpp>
#include <effect_manager/KeyLight.hpp>
#include <string>
#include <vector>
#include <memory>
#include <map>

class ASUSAuraKeyboardDevice :
    public IKeyboardDevice
{
public:
    ASUSAuraKeyboardDevice(AuraServiceLib::IAuraSyncKeyboardPtr native_dev);
    ~ASUSAuraKeyboardDevice();

    // Inherited via IKeyboardDevice
    virtual std::string get_name() override;
    virtual void apply_colors() override;
    virtual KeyLight* key_begin() override;
    virtual KeyLight* key_end() override;
    virtual float get_width() override;
    virtual float get_height() override;
private:
    //ASUS Aura keyboards seem to report the wrong width (atleast on asus falchion), so we calculate it from the furthest away key
    float actual_width;
    AuraServiceLib::IAuraSyncKeyboardPtr _native_dev;
    std::map<unsigned short, AuraServiceLib::IAuraRgbKeyPtr> key_translation;
    std::vector<KeyLight> _raster;
};

