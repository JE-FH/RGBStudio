export type Listener<TArgs extends any[]> = (...args: TArgs) => void;

export class CSEvent<TListener extends Listener<any[]>> {
	private listeners: TListener[];
	constructor() {
		this.listeners = [];
	}

	add_listener(listener: TListener): void {
		this.listeners.push(listener);
	}

	remove_listener(listener: TListener): void {
		this.listeners = this.listeners.filter((l) => {
			return l != listener;
		});
	}

	remove_listeners(): void {
		this.listeners = [];
	}

	call(...args: Parameters<TListener>) {
		this.listeners.forEach((listener) => {
			listener(...args);
		});
	}
}