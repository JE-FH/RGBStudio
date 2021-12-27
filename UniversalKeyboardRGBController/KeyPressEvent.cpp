#include "KeyPressEvent.h"

KeyPressEvent::KeyPressEvent(unsigned char os_specific_code)
{
	this->os_specific_code = os_specific_code;
}

std::string KeyPressEvent::describe()
{
	return "KeyPressEvent(" + std::to_string(this->os_specific_code) + ")";
}
