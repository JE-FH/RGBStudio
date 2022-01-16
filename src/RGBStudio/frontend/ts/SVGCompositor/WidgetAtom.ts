import { Widget, Position } from "./Widget";

export abstract class WidgetAtom extends Widget {
	constructor(relative_pos: Position) {
		super(relative_pos);
	}

	tree_walk(operation: (widget: Widget) => void): void {
		operation(this);
	}
}