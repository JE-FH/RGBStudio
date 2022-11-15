#include <event_trigger_runner/LifetimeEventSource.hpp>
#include <event_trigger_runner/LifetimeEvent.hpp>
#include <iostream>
LifetimeEventSource::LifetimeEventSource() {
    _starting = false;
    _stopping = false;
}

void LifetimeEventSource::poll_events(EventQueue& event_queue) {
    if (_starting) {
        event_queue.push(std::make_unique<LifetimeEvent>(LifetimeEventType::STARTING));
    }
    if (_stopping) {
        event_queue.push(std::make_unique<LifetimeEvent>(LifetimeEventType::STOPPING));
    }
    _starting = false;
    _stopping = false;
}

void LifetimeEventSource::starting() {
    _starting = true;
}

void LifetimeEventSource::stopping() {
    _stopping = true;
}