function define()
	return {
		name = "Fraction fill",
		properties = {
			color = "rgb color",
			end_trigger = "action",
			start_fraction = "number",
			end_fraction = "number"
		}
	}
end

function init(settings, dev)
	color = settings.color
	end_trigger = settings.end_trigger;
	device = dev;

	local width = device:get_width();

	target_keys = {}
	print(settings.start_fraction);
	print(settings.end_fraction);
	for i = 0, (device:get_key_count() - 1) do
		local info = device:get_key_info(i);
		if info.x >= width * settings.start_fraction and info.x < width * settings.end_fraction then
			table.insert(target_keys, i);
		end
	end

	print(width * settings.start_fraction, width * settings.end_fraction)
end

function init_instance(state, trigger_observer_dispatcher)
	trigger_observer_dispatcher:add_trigger(end_trigger, end_trigger_handler)
end

function end_trigger_handler(state, trigger_name)
	state.completed = true;
end

function draw(state, delta)
	for k,v in pairs(target_keys) do
		device:set_key_color(v, color.r, color.g, color.b);
	end
end
