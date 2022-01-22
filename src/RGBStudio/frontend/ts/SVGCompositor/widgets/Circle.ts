import { Circular } from "../trait/Circular";
import { Clickable, ClickEvent } from "../trait/Clickable";
import { CSEvent } from "../CSEvent";
import { RGBColor } from "../StyleHelper";
import { BoundingBox, Position } from "../Widget";
import { WidgetContainer } from "../WidgetContainer";
import { Resizing } from "../trait/Resizing";

interface CircleStyle {
	fill?: RGBColor;
	classes?: string[];
}

export class Circle 
	extends WidgetContainer 
	implements Clickable, Circular, Resizing
{
	private circle_element: SVGCircleElement;

	constructor(radius: number, circle_style: CircleStyle, relative_pos?: Position) {
		super(relative_pos ?? {x: 0, y: 0});
		this._radius = radius;
		this._Clicked = new CSEvent();
		this._Resized = new CSEvent();

		this.circle_element = document.createElementNS("http://www.w3.org/2000/svg", "circle");
		this.circle_element.setAttribute("r", this._radius.toString());

		if (circle_style.classes) {
			circle_style.classes.forEach((_class) => {
				this.circle_element.classList.add(_class);
			})
		}

		if (circle_style.fill)
			this.circle_element.setAttribute("fill", circle_style.fill.svg_color());
		

		this.circle_element.addEventListener("pointerdown", (ev) => {
			this._Clicked.call(ev);
		});
	}
	
	
	get_elements(): SVGElement[] {
		return [this.circle_element];
	}

	override position_updated(): void {
		let absolute = this.get_absolute_position();
		
		this.circle_element.setAttribute("cx", (absolute.x + this.radius).toString());
		this.circle_element.setAttribute("cy", (absolute.y + this.radius).toString());
		
		super.position_updated();
	}

	calculate_bounding_box(): BoundingBox {
		return {
			left: this.relative_pos.x,
			top: this.relative_pos.y,
			right: this.relative_pos.x + this.radius*2,
			bottom: this.relative_pos.y + this.radius*2
		};
	}
	
	//Implement Clickable
	readonly __RGBSTUDIO_SVGCOMPOSITOR_CLICKABLE_IMPLEMENTED: true = true;
	private _Clicked: ClickEvent;
	public get Clicked(): ClickEvent {
		return this._Clicked;
	}
	
	//Implement circular
	readonly __RGBSTUDIO_SVGCOMPOSITOR_CIRCULAR_IMPLEMENTED: true = true;
	
	private _radius: number;
	public get radius(): number {
		return this._radius;
	}

	resize(new_radius: number): void {
		this._radius = new_radius;
	}

	//implement Resizing
	readonly __RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true = true;
	_Resized: CSEvent<() => void>;
	get Resized(): CSEvent<() => void> {
		return this._Resized;
	}
}