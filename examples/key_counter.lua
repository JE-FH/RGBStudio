function define()
    return {
        name = "Key counter",
        properties = {
            color = "rgb color",
            interval = "number",
            stop = "action",
            increase_count = "action"
        }
    };
end

function init(settings, dev)
    Color = settings.color;
    Interval = settings.interval;
    Device = dev;
    Running = false;
    EndAction = settings.stop;
    IncreaseCount = settings.increase_count
end

function init_instance(state, trigger_observer_dispatcher)
    if (Running) then
        state.completed = true;
    end
    state.count = 0;
    Running = true;
    trigger_observer_dispatcher:add_trigger(EndAction, EndTriggerHandler)
    trigger_observer_dispatcher:add_trigger(IncreaseCount, IncreaseCountHandler)
end

function EndTriggerHandler(state, trigger_name)
	state.completed = true;
    Running = false;
end

function IncreaseCountHandler(state, trigger_name)
    state.count = state.count + 1
end

function draw(state, delta)
	for i = 0, (Device:get_key_count() - 1) do
        if (i >= state.count) then
            break;
        end
        Device:set_key_color(i, Color.r, Color.g, Color.b);
    end
end
