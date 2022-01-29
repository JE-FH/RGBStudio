import { CSEvent } from "../CSEvent";
import { ResizeableRectangular } from "../trait/Rectangular";
import { implements_resizing, ResizeEvent, Resizing } from "../trait/Resizing";
import { BoundingBox, Position, Widget } from "../Widget";
import { WidgetContainer } from "../WidgetContainer";

export interface FlexBoxProps {
	min_distance: number;
	relative_pos?: Position
}

export class FlexBox 
	extends WidgetContainer
	implements ResizeableRectangular 
{
	private _min_width: number;
	private _min_height: number;
	private _min_distance: number;
	private _width: number;
	private _height: number;
	
	constructor(props: FlexBoxProps) {
		super(props.relative_pos ?? {x: 0, y: 0});
		this.Resized = new CSEvent();
		this._width = 0;
		this._height = 0;
		this._min_width = 0;
		this._min_height = 0;
		this._min_distance = props.min_distance;
		this.recalculate_layout = this.recalculate_layout.bind(this);
	}

	override add(widget: Widget) {
		if (implements_resizing(widget)) {
			widget.Resized.add_listener(this.recalculate_layout);
		}

		super.add(widget);
	
		this.recalculate_layout();
	}

	override remove(widget: Widget) {
		if (implements_resizing(widget)) {
			widget.Resized.remove_listener(this.recalculate_layout);
		}

		super.remove(widget);

		this.recalculate_layout();
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

	recalculate_layout(): void {
		let old_min_width = this._min_width;
		let old_min_height = this._min_height;
		let old_width = this._width;
		let old_height = this._height;

		let new_min_width = 0;
		let new_min_height = 0;
		
		let elements_length = 0;

		let bb_map: Map<Widget, BoundingBox> = new Map();

		for (let child of this.get_children()) {
			let bb = child.calculate_bounding_box();
			let thing = {
				width: bb.right - bb.left,
				height: bb.bottom - bb.top
			};
			new_min_width += thing.width + this._min_distance;
			new_min_height = Math.max(thing.height, new_min_height);
			
			elements_length += thing.width;

			bb_map.set(child, bb);
		}

		if (new_min_width > 0) {
			new_min_width -= this._min_distance;
		}

		this._min_width = new_min_width;
		this._min_height = new_min_height;

		if (this._min_width > this.width || this._min_height > this.height) {
			this._width = Math.max(this._min_width, this._width);
			this._height = Math.max(this._min_height, this._height);
		}
		
		let distance: number = 0;
		let children_count = this.get_children().length;
		
		if (children_count > 1) {
			distance = (this.width - elements_length) / (this.get_children().length - 1);
		}

		console.log(`${distance} = (${this.width} - ${elements_length}) / ${this.get_children().length - 1}`);

		let current_left = 0;
		for (let child of this.get_children()) {
			child.move_to_relative({x: current_left, y: child.get_relative_position().y});
			let bb = bb_map.get(child)!;
			current_left += distance + (bb.right - bb.left);
		}
		
		
		if (this.width != old_width || this.height != old_height ||this._min_width != old_min_width || this._min_height != old_min_height) {
			this.Resized.call();
		}
	}
	
	//Implement resizing
	__RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true = true;
	Resized: ResizeEvent;

	//Implement rectangular
	__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: 2 = 2;
	
	get width(): number {
		return this._width;
	}

	get height(): number {
		return this._height;
	}

	resize(new_width: number, new_height: number): void {
		this._width = Math.max(this._min_width, new_width);
		this._height = Math.max(this._min_height, new_height);

		this.recalculate_layout();
	}

	get minimum_width(): number {
		return this._min_width;
	}

	get minimum_height(): number {
		return this._min_height;
	}
}