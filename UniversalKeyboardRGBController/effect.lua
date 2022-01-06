function init(settings)
	red = settings.red;
	green = settings.green;
	blue = settings.blue;
	stop_time = settings.time;
	
end

function init_instance(state, trigger_observer_dispatcher)
	state.delta_counter = 0;
	state.first_time = true;
	state.target_keys = {};
end

function draw(state, delta, device)
	if (state.first_time) then
		local width = device:get_width();

		for i = 0,(device:get_key_count() - 1) do
			local info = device:get_key_info(i);
			if info.x < width/2 then
				table.insert(state.target_keys, i);
			end
		end
		state.first_time = false;
	end
	state.delta_counter = state.delta_counter + delta;
	
	for k,v in pairs(state.target_keys) do
		device:set_key_color(v, red, green, blue);
	end

	if (state.delta_counter > stop_time) then
		state.completed = true;
		return;
	end
end
