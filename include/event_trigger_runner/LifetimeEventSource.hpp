#pragma once
#include <event_trigger_runner/IEventSource.hpp>

class LifetimeEventSource : public IEventSource {
public:
    LifetimeEventSource();
    void poll_events(EventQueue& event_queue) override;

    void starting();

    void stopping();
private:
    bool _starting;
    bool _stopping;
};
