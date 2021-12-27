#include "KeyReleaseEvent.h"

KeyReleaseEvent::KeyReleaseEvent(unsigned char os_specific_code)
{
    this->os_specific_code = os_specific_code;
}

std::string KeyReleaseEvent::describe()
{
    return "KeyReleaseEvent(" + std::to_string(os_specific_code) + ")";
}
