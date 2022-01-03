#pragma once
#include "IKeyboardDevice.h"

class Effect {
public:
	virtual ~Effect() {}
	
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
	virtual void draw(IKeyboardDevice* device, double delta) = 0;
protected:
	Effect(int layer) {
		this->layer = layer;
		completed = false;
	}

	void mark_completed() {
		completed = true;
	}

	bool completed;
};