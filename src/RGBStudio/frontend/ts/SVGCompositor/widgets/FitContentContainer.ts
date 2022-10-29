import { CSEvent } from "../CSEvent";
import { Rectangular } from "../trait/Rectangular";
import { implements_resizing, ResizeEvent, Resizing } from "../trait/Resizing";
import { BoundingBox, Position, Widget } from "../Widget";
import { WidgetContainer } from "../WidgetContainer";

export class FitContentContainer 
	extends WidgetContainer 
	implements Rectangular, Resizing
{
	private _width: number;
	private _height: number;
	
	constructor(relative_position?: Position) {
		super(relative_position ?? {x: 0, y: 0});
		this.Resized = new CSEvent();
		this._width = 0;
		this._height = 0;
		this.recalculate_size = this.recalculate_size.bind(this);
	}
	
	calculate_bounding_box(): BoundingBox {
		return {
			left: this.relative_pos.x,
			top: this.relative_pos.y,
			right: this.relative_pos.x + this._width,
			bottom: this.relative_pos.y + this._height
		}
	}
	
	override add<T extends Widget>(widget: T): T {
		if (implements_resizing(widget)) {
			widget.Resized.add_listener(this.recalculate_size);
		}
		super.add(widget);
		this.recalculate_size();

		return widget;
	}
	
	override remove(widget: Widget): void {
		if (implements_resizing(widget)) {
			widget.Resized.remove_listener(this.recalculate_size);
		}
		super.remove(widget);
		this.recalculate_size();
	}

	get_elements(): SVGElement[] {
		return [];
	}

	protected recalculate_size() {
		let new_width = 0;
		let new_height = 0;
		
		for (let child of this.get_children()) {
			let bb = child.calculate_bounding_box();

			new_width = Math.max(bb.right, new_width);
			new_height = Math.max(bb.bottom, new_height);
		}

		if (new_width != this.width || new_height != this.height) {
			this._width = new_width;
			this._height = new_height;
			this.Resized.call();
		}
	}
	
	//Implement resizing
	__RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true = true;
	Resized: ResizeEvent;

	//Implement rectangular
	__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: 1 = 1;
	get width(): number {
		return this._width;
	}
	get height(): number {
		return this._height;
	}
}