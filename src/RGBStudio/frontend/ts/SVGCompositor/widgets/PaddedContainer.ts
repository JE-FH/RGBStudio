import { CSEvent } from "../CSEvent";
import { FitContentContainer } from "./FitContentContainer";
import { Rectangular, ResizeableRectangular } from "../trait/Rectangular";
import { ResizeEvent, Resizing } from "../trait/Resizing";
import { BoundingBox, Position, Widget } from "../Widget";
import { WidgetContainer } from "../WidgetContainer";

export interface Padding {
	left: number;
	top: number;
	right: number;
	bottom: number;
}

export function padding(all_sides: number): Padding;
export function padding(horizontal: number, vertical: number): Padding;
export function padding(left: number, top: number, right: number, bottom: number): Padding;
export function padding(left: number, top?: number, right?: number, bottom?: number): Padding {
	right = right ?? left;
	top = top ?? left;
	bottom = bottom ?? top;
	return {
		left,
		top,
		right,
		bottom
	};
}

export class PaddedContainer
	extends WidgetContainer
	implements Resizing, ResizeableRectangular
{
	private _padding: Padding;	
	private _inner_container: FitContentContainer;
	private _width: number;
	private _height: number;

	constructor(padding: Padding, relative_position?: Position) {
		super(relative_position ?? {x: 0, y: 0});
		this._padding = padding;
		this._inner_container = new FitContentContainer({
			x: this._padding.left,
			y: this._padding.top
		});
		this._width = this.minimum_width;
		this._height = this.minimum_height;
		this.Resized = new CSEvent();

		this._inner_container.Resized.add_listener(() => {
			this.resize(this.minimum_width, this.minimum_height);
		})

		super.add(this._inner_container);
	}
	
	override add(widget: Widget) {
		this._inner_container.add(widget);
	}
	
	override remove(widget: Widget) 	{
		this._inner_container.remove(widget);
	}
	
	override get_children(): readonly Widget[] {
		return this._inner_container.get_children();
	}
	
	get_elements(): SVGElement[] {
		return [];
	}
	
	calculate_bounding_box(): BoundingBox {
		return {
			left: this.relative_pos.x,
			top: this.relative_pos.y,
			right: this.relative_pos.x + this.width,
			bottom: this.relative_pos.y + this.height
		};
	}

	//Implement Resizing
	__RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true = true;
	Resized: ResizeEvent;

	//Implement resizeablerectangular
	__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: 2 = 2;
	get width(): number {
		return this._width;
	}

	get height(): number {
		return this._height;
	}

	resize(new_width: number, new_height: number) {
		if (new_width < this.minimum_width) {
			new_width = this.minimum_width;
		}

		if (new_height < this.minimum_height) {
			new_height = this.minimum_height;
		}

		if (new_width == this._width && new_height == this._height) {
			return;
		}

		this._width = new_width;
		this._height = new_height;

		this.Resized.call();

		this._inner_container.move_to_relative({
			x: (this.width - this._inner_container.width) / 2,
			y: (this.height - this._inner_container.height) / 2
		});

	}

	get minimum_width(): number {
		return this._inner_container.width + this._padding.left + this._padding.right;
	}

	get minimum_height(): number {
		return this._inner_container.height + this._padding.top + this._padding.bottom;
	}
}