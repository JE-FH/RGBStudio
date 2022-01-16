export type Listener<TArgs extends any[]> = (...args: TArgs) => void;

export class Event<TArgs extends any[]> {
	private listeners: Listener<TArgs>[];
	constructor() {
		this.listeners = [];
	}

	add_listener(listener: Listener<TArgs>): void {
		this.listeners.push(listener);
	}

	remove_listener(listener: Listener<TArgs>): void {
		this.listeners = this.listeners.filter((l) => {
			return l != listener;
		});
	}

	remove_listeners(): void {
		this.listeners = [];
	}

	call(...args: TArgs) {
		this.listeners.forEach((listener) => {
			listener(...args);
		});
	}
}