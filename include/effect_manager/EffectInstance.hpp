#pragma once
#include <device_adapter_loader/IKeyboardDevice.hpp>
#include <memory>

class EffectInstance {
public:
	virtual ~EffectInstance() {}
	
	int layer;

	/// <summary>
	/// Checks if the effect has completed and will never affect the keyboard again 
	/// </summary>
	bool is_completed() {
		return completed;
	}
	
	/// <summary>
	/// Call to draw the effect
	/// </summary>
	/// <param name="delta">The amount of time since last call</param>
	virtual void draw(double delta) = 0;
protected:
	EffectInstance(int layer, std::shared_ptr<IKeyboardDevice> keyboard_device) {
		this->layer = layer;
		this->_keyboard_device = std::move(keyboard_device);
		completed = false;
	}

	void mark_completed() {
		completed = true;
	}

	bool completed;

	std::shared_ptr<IKeyboardDevice> _keyboard_device;
};