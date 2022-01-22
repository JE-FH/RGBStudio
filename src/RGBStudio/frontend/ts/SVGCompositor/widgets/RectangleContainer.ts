import { Clickable, ClickEvent } from "../trait/Clickable";
import { CSEvent } from "../CSEvent";
import { Rectangular, ResizeableRectangular } from "../trait/Rectangular";
import { RGBColor } from "../StyleHelper";
import { BoundingBox, Position, Widget } from "../Widget";
import { WidgetContainer } from "../WidgetContainer";
import { Resizing } from "../trait/Resizing";
import { PaddedContainer, Padding } from "./PaddedContainer";

interface RectStyle {
	fill?: RGBColor;
	classes?: string[];
	rx?: number;
	ry?: number;
}

export class RectangleContainer 
	extends PaddedContainer 
	implements Clickable
{
	readonly __RGBSTUDIO_SVGCOMPOSITOR_CLICKABLE_IMPLEMENTED: true = true;

	private rect: SVGRectElement;
	private _Clicked: ClickEvent;
	
	public get Clicked(): ClickEvent {
		return this._Clicked;
	}
	
	constructor(padding: Padding, rect_style: RectStyle, relative_pos?: Position) {
		super(padding, relative_pos);
		this._Clicked = new CSEvent();
		this.rect = document.createElementNS("http://www.w3.org/2000/svg", "rect");
		let absolute = this.get_absolute_position();
		
		this.rect.setAttribute("x", absolute.x.toString());
		this.rect.setAttribute("y", absolute.y.toString());
		
		this.rect.setAttribute("width", this.width.toString());
		this.rect.setAttribute("height", this.height.toString());
		
		if (rect_style.fill)
			this.rect.setAttribute("fill", rect_style.fill.svg_color());
		
		if (rect_style.classes) {
			rect_style.classes.forEach((_class) => {
				this.rect.classList.add(_class);
			});
		}

		if (rect_style.rx) {
			this.rect.setAttribute("rx", rect_style.rx.toString());
		}
		
		if (rect_style.ry) {
			this.rect.setAttribute("ry", rect_style.ry.toString());
		}

		this.rect.addEventListener("pointerdown", (ev) => {
			this.Clicked.call(ev);
		});

		this.Resized.add_listener(() => {
			this.rect.setAttribute("width", this.width.toString());
			this.rect.setAttribute("height", this.height.toString());
		});
	}
	
	
	override position_updated(): void {
		let absolute = this.get_absolute_position();
		
		this.rect.setAttribute("x", absolute.x.toString());
		this.rect.setAttribute("y", absolute.y.toString());
		
		super.position_updated();
	}
	
	override get_elements(): SVGElement[] {
		return [this.rect];
	}
}