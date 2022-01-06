function init(settings)
	red = settings.red;
	green = settings.green;
	blue = settings.blue;
	stop_time = settings.time;
end

function init_instance(state, trigger_observer_dispatcher)
	state.delta_counter = 0;
end

function draw(state, delta, device)
	state.delta_counter = state.delta_counter + delta;
	
	if (state.delta_counter > stop_time) then
		state.completed = true;
		return;
	end

	device:fill(red, green, blue);
end
