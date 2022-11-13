#include <event_trigger_runner/KeyEvent.hpp>
#include <sstream>
#include <format>

KeyEvent::KeyEvent(unsigned char os_specific_code, unsigned char scancode, bool pressed, bool repeated)
{
	this->pressed = pressed;
	this->repeated = repeated;
	this->os_specific_code = os_specific_code;
	this->scancode = scancode;
}

std::string KeyEvent::describe()
{
	return std::format("KeyEvent(0x{:x}, {}, {}, {})", os_specific_code, scancode, pressed, repeated);
}
