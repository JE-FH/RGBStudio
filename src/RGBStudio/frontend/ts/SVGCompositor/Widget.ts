import {Event} from "./Event";
import { WidgetContainer } from "./WidgetContainer";

export interface Position {
	x: number;
	y: number;
}

export type ClassConstructor<T> = (new (...args: any[]) => T);

export abstract class Widget {
	private _changed_visual_tree: Event<[]>;
	
	protected relative_pos: Position;
	
	private _parent: WidgetContainer | null;
	
	protected get parent(): WidgetContainer | null {
		return this._parent;
	}
	
	public get changed_visual_tree(): Event<[]> {
		return this._changed_visual_tree;
	}

	constructor(relative_pos: Position) {
		this._parent = null;

		this._changed_visual_tree = new Event<[]>();

		this.relative_pos = {
			x: relative_pos.x,
			y: relative_pos.y
		};
	}

	abstract update(): void;

	//Gets the SVGElements that constitute this Widget, it does not return the child SVGElements
	abstract get_elements(): SVGElement[];
	
	//This walks the entire tree as a tree, meaning this should be overrided if a component alters the default struct like children being different
	abstract tree_walk(operation: (widget: Widget) => void): void;

	get_absolute_position(): Position {
		let parent_pos = this.parent?.get_absolute_position() ?? {x: 0, y: 0};
		return {
			x: this.relative_pos.x + parent_pos.x,
			y: this.relative_pos.y + parent_pos.y
		};
	}

	get_relative_position(): Position {
		return {
			x: this.relative_pos.x,
			y: this.relative_pos.y
		};
	}

	//Move this widget to a position relative to its parent
	move_to_relative(new_relative_pos: Position): void {
		this.relative_pos = new_relative_pos;
		this.update();
	}

	//Move this widget to an absolute position (relative to the target_svg)
	move_to_absolute(absolute_pos: Position): void {
		let parent_pos = this.parent?.get_absolute_position() ?? {x: 0, y: 0};
		this.relative_pos.x = absolute_pos.x - parent_pos.x;
		this.relative_pos.y = absolute_pos.y - parent_pos.y;
		this.update();
	}

	//Dont know what travelling up a tree is called, so it has this name
	travel_up_to_match(condition: (widget: Widget) => boolean): Widget | undefined {
		return condition(this) ? this : this.parent?.travel_up_to_match?.(condition);
	}

	travel_up_to_type<T>(type: ClassConstructor<T>): T | undefined {
		return this.travel_up_to_match((widget) => widget instanceof type) as unknown as T;
	}

	protected set_parent(new_parent: WidgetContainer | null) {
		this._parent = new_parent;
	}
}