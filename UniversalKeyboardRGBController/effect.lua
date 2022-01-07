function init(settings, dev)
	red = settings.red;
	green = settings.green;
	blue = settings.blue;
	stop_time = settings.time;
	device = dev;

	local width = device:get_width();

	target_keys = {}

	for i = 0, (device:get_key_count() - 1) do
		local info = device:get_key_info(i);
		if info.x > width * settings.start_fraction and info.x < width * settings.end_fraction then
			table.insert(target_keys, i);
		end
	end
end

function init_instance(state, trigger_observer_dispatcher)
	state.delta_counter = 0;
end

function draw(state, delta)
	state.delta_counter = state.delta_counter + delta;
	
	for k,v in pairs(target_keys) do
		device:set_key_color(v, red, green, blue);
	end

	if (state.delta_counter > stop_time) then
		state.completed = true;
		return;
	end
end
