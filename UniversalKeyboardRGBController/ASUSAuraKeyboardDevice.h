#pragma once
#include <Windows.h>
#import "libid:F1AA5209-5217-4B82-BA7E-A68198999AFA"
#include "IKeyboardDevice.h"
#include "ASUSAuraKeyLight.h"
#include "IKeyLight.h"
#include <string>
#include <vector>
#include <memory>

class ASUSAuraKeyboardDevice :
    public IKeyboardDevice
{
public:
    ASUSAuraKeyboardDevice(AuraServiceLib::IAuraSyncKeyboardPtr native_dev);
    ~ASUSAuraKeyboardDevice();

    // Inherited via IKeyboardDevice
    virtual std::string get_name() override;
    virtual void apply_colors() override;
    virtual IKeyLight** key_begin() override;
    virtual IKeyLight** key_end() override;
    virtual float get_width() override;
    virtual float get_height() override;
    virtual void fill(const RGBColor& color) override;
    virtual void fill(const RGBColor& color, float alpha) override;
private:
    //ASUS Aura keyboards seem to report the wrong width (atleast on asus falchion), so we calculate it from the furthest away key
    float actual_width;
    AuraServiceLib::IAuraSyncKeyboardPtr _native_dev;
    std::vector<ASUSAuraKeyLight> _key_lights;
    std::vector<IKeyLight*> _key_lights_raw_list;
};

