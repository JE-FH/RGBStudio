#include <event_trigger_runner/default_triggers/LifetimeTrigger.hpp>
#include <event_trigger_runner/LifetimeEvent.hpp>

LifetimeTrigger::LifetimeTrigger(std::string trigger_name)
    : Trigger(trigger_name) 
{
    
}

bool LifetimeTrigger::should_trigger(Event& ev, std::string& trigger_sub_name) {
    if (auto lifetime_event = dynamic_cast<LifetimeEvent*>(&ev)) {
        if (lifetime_event->GetType() == LifetimeEventType::STARTING) {
            trigger_sub_name = "starting";
        } else {
            trigger_sub_name = "stopping";
        }
        return true;
    }
    return false;
}