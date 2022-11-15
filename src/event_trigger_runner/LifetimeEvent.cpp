#include <event_trigger_runner/LifetimeEvent.hpp>
#include <format>

LifetimeEvent::LifetimeEvent(LifetimeEventType type) {
    _type = type;
}

LifetimeEventType LifetimeEvent::GetType() const {
    return _type;
}

std::string LifetimeEvent::describe() {
    std::string lifetimeEventName = "";
    if (_type == LifetimeEventType::STARTING) {
        lifetimeEventName = "STARTING";
    } else {
        lifetimeEventName = "STOPPING";
    }

    return std::format("LifetimeEvent({})", lifetimeEventName);
}