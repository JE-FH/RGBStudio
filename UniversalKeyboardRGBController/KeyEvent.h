#pragma once
#include "Event.h"
class KeyEvent :
    public Event
{
public:
    KeyEvent(unsigned char os_specific_code, unsigned char scancode, bool pressed, bool repeated);
    
    bool pressed;
    bool repeated;
    unsigned long os_specific_code;
    unsigned char scancode;

    // Inherited via Event
    virtual std::string describe() override;
};

