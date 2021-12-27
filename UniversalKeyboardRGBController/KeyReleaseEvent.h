#pragma once
#include "Event.h"
class KeyReleaseEvent :
    public Event
{
public:
    KeyReleaseEvent(unsigned char os_specific_code);
    unsigned char os_specific_code;

    // Inherited via Event
    virtual std::string describe() override;
};

