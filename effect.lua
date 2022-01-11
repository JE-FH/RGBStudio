function init(settings, dev)
	red = settings.red;
	green = settings.green;
	blue = settings.blue;
	end_trigger = settings.end_trigger;
	device = dev;

	local width = device:get_width();

	target_keys = {}

	for i = 0, (device:get_key_count() - 1) do
		local info = device:get_key_info(i);
		if info.x >= width * settings.start_fraction and info.x < width * settings.end_fraction then
			table.insert(target_keys, i);
		end
	end
end

function init_instance(state, trigger_observer_dispatcher)
	trigger_observer_dispatcher:add_trigger(end_trigger, end_trigger_handler)
end

function end_trigger_handler(state, trigger_name)
	state.completed = true;
end

function draw(state, delta)
	for k,v in pairs(target_keys) do
		device:set_key_color(v, red, green, blue);
	end
end
