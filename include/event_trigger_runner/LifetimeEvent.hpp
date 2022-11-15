#pragma once
#include "Event.hpp"

enum class LifetimeEventType {
    STARTING,
    STOPPING
};

class LifetimeEvent :
    public Event
{
    LifetimeEventType _type;
public:
    LifetimeEvent(LifetimeEventType type);
    
    LifetimeEventType GetType() const;

    // Inherited via Event
    std::string describe() override;
};

