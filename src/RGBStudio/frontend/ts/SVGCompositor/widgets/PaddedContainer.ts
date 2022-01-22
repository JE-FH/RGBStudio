import { ElementFlags } from "../../../node_modules/typescript/lib/typescript";
import { GConstructor } from "../../util";
import { CSEvent } from "../CSEvent";
import { RGBColor } from "../StyleHelper";
import { Clickable, ClickEvent } from "../trait/Clickable";
import { Hoverable, HoverEvent } from "../trait/Hoverable";
import { implements_rectangular, implements_resizeable_rectangular, Rectangular, ResizeableRectangular } from "../trait/Rectangular";
import { implements_resizing, ResizeEvent, Resizing } from "../trait/Resizing";
import { BoundingBox, Position, Widget } from "../Widget";
import { WidgetContainer } from "../WidgetContainer";

function create_rect(class_name: string, x: number, y: number, width: number, height: number): SVGRectElement {
	let rv = document.createElementNS("http://www.w3.org/2000/svg", "rect");
	rv.classList.add(class_name);
	rv.setAttribute("x", x.toString());
	rv.setAttribute("y", y.toString());
	rv.setAttribute("width", width.toString());
	rv.setAttribute("height", height.toString());
	return rv;
}

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


export interface BackgroundStyle {
	classes?: string[];
	rx?: number;
	ry?: number;
}

export class PaddedContainer
	extends WidgetContainer
	implements ResizeableRectangular, Clickable, Hoverable
{
	private _padding: Padding;
	private _Resized: ResizeEvent;
	
	private _width: number = 0;
	public get width(): number {
		return this._width;
	}
	
	private set width(value: number) {
		this._width = value;
	}
	
	private _height: number = 0;
	public get height(): number {
		return this._height;
	}
	private set height(value: number) {
		this._height = value;
	}

	private _minimum_width: number;
	private _minimum_height: number;
	private _ignore_inner_resize: boolean;

	private inner_widget: (Widget) | null;

	private background_rect: SVGRectElement | null;

	constructor(padding: Padding, rect_style?: BackgroundStyle, relative_position?: Position) {
		super(relative_position ?? {x: 0, y: 0});
		this._padding = padding;
		this._Resized = new CSEvent();
		
		this._minimum_width = this.calculate_minimum_width();
		this._minimum_height = this.calculate_minimum_height();

		this._ignore_inner_resize = false;
		
		this.width = this.minimum_width;
		this.height = this.minimum_height;

		this.inner_widget = null;
		this.on_child_resize = this.on_child_resize.bind(this);

		if (rect_style) {
			this.background_rect = document.createElementNS("http://www.w3.org/2000/svg", "rect");
			if (rect_style.classes) {
				for (let _class of rect_style.classes) {
					this.background_rect.classList.add(_class);
				}
			}
			
			if (rect_style.rx) {
				this.background_rect.setAttribute("rx", rect_style.rx.toString());
			}
			
			if (rect_style.ry) {
				this.background_rect.setAttribute("ry", rect_style.ry.toString());
			}

			this.background_rect.setAttribute("width", this.width.toString());
			this.background_rect.setAttribute("height", this.height.toString());

			this.background_rect.addEventListener("pointerdown", (ev) => {
				this.Clicked.call(ev);
			});

			this.background_rect.addEventListener("mouseover", (ev) => {
				this.Hovered.call(ev);
			});

			this.background_rect.addEventListener("mouseleave", (ev) => {
				this.Unhovered.call(ev);
			});
		} else {
			this.background_rect = null;
		}
	}
	readonly __RGBSTUDIO_SVGCOMPOSITOR_HOVERABLE_IMPLEMENTED: true = true;
	readonly Hovered: HoverEvent = new CSEvent();
	readonly Unhovered: HoverEvent = new CSEvent();
	readonly __RGBSTUDIO_SVGCOMPOSITOR_CLICKABLE_IMPLEMENTED: true = true;
	readonly Clicked: ClickEvent = new CSEvent();

	override position_updated(): void {
		if (this.background_rect) {
			let abs = this.get_absolute_position();
			this.background_rect.setAttribute("x", abs.x.toString());
			this.background_rect.setAttribute("y", abs.y.toString());
		}
		super.position_updated();
	}

	get_elements(): SVGElement[] {
		if (this.background_rect) {
			return [this.background_rect];
		} else {
			return [];
		}
	}
	
	calculate_bounding_box(): BoundingBox {
		return {
			left: this.relative_pos.x,
			top: this.relative_pos.y,
			right: this.relative_pos.x + this.width,
			bottom: this.relative_pos.y + this.height
		};
	}

	//widget has to implement rectangular
	override add(widget: Widget): void {
		if (this.get_children().length > 0) {
			throw new Error("PaddedContainer can only have one child");
		}
		
		if (implements_resizing(widget)) {
			widget.Resized.add_listener(this.on_child_resize);
		}
		
		super.add(widget);
		
		this.inner_widget = widget;
		this.on_child_resize();
	}

	override remove(widget: Widget) {
		if (implements_resizing(widget)) {
			widget.Resized.remove_listener(this.on_child_resize);
		}

		super.remove(widget);

		this.inner_widget = null;
		this.on_child_resize();
	}

	override create_bounding_box_rect(): SVGRectElement[] {
		let abs = this.get_absolute_position();
		let left = create_rect("debug-bb-padding-highlight", abs.x, abs.y, this._padding.left, this.height);
		let top = create_rect("debug-bb-padding-highlight", abs.x + this._padding.left, abs.y, this.inner_width, this._padding.top);
		let right = create_rect("debug-bb-padding-highlight", abs.x + this.inner_width + this._padding.left, abs.y, this._padding.right, this.height);
		let bottom = create_rect("debug-bb-padding-highlight", abs.x + this._padding.left, abs.y + this.inner_height + this._padding.top, this.inner_width, this._padding.bottom);
		return super.create_bounding_box_rect().concat([left, top, right, bottom]);
	}

	private calculate_minimum_width(): number {
		let rv = this._padding.left + this._padding.right;

		if (implements_resizeable_rectangular(this.inner_widget)) {
			rv += this.inner_widget.minimum_width;

		} else if (implements_rectangular(this.inner_widget)) {
			rv += (this.inner_widget.width);

		} else if (this.inner_widget != null) {
			let bb = this.inner_widget.calculate_bounding_box();
			rv += (bb.right - bb.left)
		}
		return rv;
	}
	
	private calculate_minimum_height(): number {
		let rv = this._padding.top + this._padding.bottom;

		if (implements_resizeable_rectangular(this.inner_widget)) {
			rv += this.inner_widget.minimum_height;

		} else if (implements_rectangular(this.inner_widget)) {
			rv += (this.inner_widget.height);

		} else if (this.inner_widget != null) {
			let bb = this.inner_widget.calculate_bounding_box();
			rv += (bb.bottom - bb.top)
		}
		return rv;
	}
	
	__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: 2 = 2;
	public get minimum_width(): number {
		return this._minimum_width;
	}
	
	private set minimum_width(value: number) {
		this._minimum_width = value;
	}
	
	public get minimum_height(): number {
		return this._minimum_height;
	}
	
	private set minimum_height(value: number) {
		this._minimum_height = value;
	}
	
	public __RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true = true;
	get Resized(): ResizeEvent {
		return this._Resized;
	}
	
	resize(new_width: number, new_height: number): boolean {
		new_width = Math.max(new_width, this.minimum_width);
		new_height = Math.max(new_height, this.minimum_height);
		
		if (new_width == this.width && new_height == this.height) {
			return false;
		}
		
		this.width = new_width;
		this.height = new_height;

		if (this.background_rect) {
			this.background_rect.setAttribute("width", this.width.toString());
			this.background_rect.setAttribute("height", this.height.toString());
		}

		if (this.inner_widget == null) {
			this.Resized.call();
			return true;
		}
		
		if (implements_resizeable_rectangular(this.inner_widget)) {
			this._ignore_inner_resize = true;
			this.inner_widget.resize(this.inner_width, this.inner_height);
			this._ignore_inner_resize = false;
		}
		
		let actual_innner_bb = this.inner_widget.calculate_bounding_box();

		this.inner_widget.move_to_relative({
			x: (this.inner_width - (actual_innner_bb.right - actual_innner_bb.left)) / 2 + this._padding.left,
			y: (this.inner_height - (actual_innner_bb.bottom - actual_innner_bb.top)) / 2 + this._padding.top
		});
		
		this.minimum_width = this.calculate_minimum_width();
		this.minimum_height = this.calculate_minimum_height();
		
		this.Resized.call();
		return true;
	}
	
	private get inner_width(): number {
		return this.width - this._padding.left - this._padding.right;
	}
	
	private get inner_height(): number {
		return this.height - this._padding.top - this._padding.bottom;
	}
	
	private on_child_resize() {
		if (this._ignore_inner_resize) {
			return;
		}
		if (this.inner_widget == null) {
			this.resize(0, 0);
			return;
		}

		let actual_innner_bb = this.inner_widget.calculate_bounding_box();

		this.inner_widget.move_to_relative({
			x: (this.inner_width - (actual_innner_bb.right - actual_innner_bb.left)) / 2 + this._padding.left,
			y: (this.inner_height - (actual_innner_bb.bottom - actual_innner_bb.top)) / 2 + this._padding.top
		});

		this.minimum_width = this.calculate_minimum_width();
		this.minimum_height = this.calculate_minimum_height();
	
		let new_width = Math.max(this.width, this.minimum_width);
		let new_height = Math.max(this.height, this.minimum_height);
		if (this.resize(new_width, new_height)) {
			//Resized was already called by resize
			return;
		}

		this.Resized.call();
		
	}
}
