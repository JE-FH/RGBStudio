import { CSEvent } from "../CSEvent";
import { implements_resizeable_rectangular, Rectangular, ResizeableRectangular } from "../trait/Rectangular";
import { Resizing, ResizeEvent, ResizeEventHandler, implements_resizing } from "../trait/Resizing";
import { BoundingBox, Position, Widget } from "../Widget";
import { WidgetContainer } from "../WidgetContainer";

export enum Orientation {
	VERTICAL,
	HORIZONTAL
}

export interface StackPanelProps {
	orientation: Orientation;
	item_spacing: number,
	relative_pos?: Position
};

export class StackPanel 
	extends WidgetContainer
	implements Resizing, ResizeableRectangular
{
	private _min_perpendicular_size: number;
	private _perpendicular_size: number;
	private _width: number;
	private _height: number;
	private _orientation: Orientation;
	private _item_spacing: number;

	constructor(props: StackPanelProps) {
		super(props.relative_pos ?? {x: 0, y: 0});
		this._width = 0;
		this._height = 0;
		this._min_perpendicular_size = 0;
		this._perpendicular_size = 0;
		this._orientation = props.orientation;
		this._item_spacing = props.item_spacing;
		this.recalculate_layout = this.recalculate_layout.bind(this);
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
	
	private recalculate_layout() {
		let new_width = 0;
		let new_height = 0;
		
		for (let child of this.get_children()) {
			let bbox = child.calculate_bounding_box();
			if (this._orientation == Orientation.HORIZONTAL) {
				if (implements_resizeable_rectangular(child)) {
					new_height = Math.max(new_height, child.minimum_height);
				} else {
					new_height = Math.max(new_height, bbox.bottom - bbox.top);
				}
				
				child.move_to_relative({x: new_width, y: 0});
				
				new_width += bbox.right - bbox.left + this._item_spacing;
			} else {
				if (implements_resizeable_rectangular(child)) {
					new_width = Math.max(new_width, child.minimum_width);
				} else {
					new_width = Math.max(new_width, bbox.right - bbox.left);
				}
				
				child.move_to_relative({x: 0, y: new_height});
				
				new_height += bbox.bottom - bbox.top + this._item_spacing;
			}
		}
		
		if (this._orientation == Orientation.HORIZONTAL) {
			new_width -= this._item_spacing;
		} else {
			new_height -= this._item_spacing;
		}

		if (this._orientation == Orientation.HORIZONTAL) {
			this._min_perpendicular_size = new_height;
		} else {
			this._min_perpendicular_size = new_width;
		}

		this._perpendicular_size = Math.max(this._perpendicular_size, this._min_perpendicular_size);
		
		if (this._orientation == Orientation.HORIZONTAL) {
			new_height = this._perpendicular_size;
		} else {
			new_width = this._perpendicular_size;
		}

		console.log(new_width, new_height);
		
		this._width = new_width;
		this._height = new_height;
		this.Resized.call();
		
		this.get_children().forEach((child) => {
			if (implements_resizeable_rectangular(child)) {
				if (this._orientation == Orientation.HORIZONTAL) {
					child.resize(child.width, this._perpendicular_size);
				} else {
					child.resize(this._perpendicular_size, child.height);
				}
			}
		})
	}
	
	//Implement resizing
	__RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true = true;
	readonly Resized: ResizeEvent = new CSEvent();
	
	//Implement resizeable rectangular
	readonly __RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: 2 = 2;

	get width(): number {
		return this._width;
	}

	get height(): number {
		return this._height;
	}

	resize(new_width: number, new_height: number): void {
		if (this._orientation == Orientation.HORIZONTAL) {
			if (this.height == new_height) {
				return;
			}
			this._perpendicular_size = new_height;
		} else {
			if (this.width == new_width) {
				return;
			}
			this._perpendicular_size= new_width;
		}
		
		this.recalculate_layout();
	}

	public get minimum_width(): number {
		if (this._orientation == Orientation.VERTICAL) {
			return this._min_perpendicular_size;
		}
		
		return this.width;
	}

	public get minimum_height(): number {
		if (this._orientation == Orientation.HORIZONTAL) {
			return this._min_perpendicular_size;
		}
		
		return this.height;
	}
}