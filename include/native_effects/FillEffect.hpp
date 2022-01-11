#pragma once
#include <effect_manager/Effect.hpp>
#include <event_trigger_runner/TriggerObserver.hpp>
#include <event_trigger_runner/TriggerObserverDispatcher.hpp>
#include <memory>

class FillEffect :
    public Effect, private TriggerObserver
{
public:
    FillEffect(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device, std::string stop_trigger, RGBColor color, TriggerObserverDispatcher& trigger_observer_dispatcher);
    // Inherited via Effect
    virtual void draw(double delta) override;
private:
    RGBColor _color;

    // Inherited via ITriggerObserver
    virtual void Trigger(const std::string& trigger_name) override;
};

