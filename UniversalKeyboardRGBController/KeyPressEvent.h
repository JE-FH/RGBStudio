#pragma once
#include "Event.h"
class KeyPressEvent :
    public Event
{
public:
    KeyPressEvent(unsigned char os_specific_code);
    unsigned char os_specific_code;

    // Inherited via Event
    virtual std::string describe() override;
};

