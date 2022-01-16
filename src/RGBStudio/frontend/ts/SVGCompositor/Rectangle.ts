import { Dragifier } from "./Dragifier";
import { RGBColor } from "./StyleHelper";
import { SVGCompositor } from "./SVGCompositor";
import { Position, Widget } from "./Widget";
import { WidgetContainer } from "./WidgetContainer";

interface RectStyle {
	width: number;
	height: number;
	fill: RGBColor;
	rx?: number;
	ry?: number;
}

export class Rectangle extends WidgetContainer {
	private width: number;
	private height: number;
	private rect: SVGRectElement;
	private dragifier?: Dragifier;
	constructor(relative_pos: Position, rect_style: RectStyle) {
		super(relative_pos);
		this.width = rect_style.width;
		this.height = rect_style.height;
		
		this.rect = document.createElementNS("http://www.w3.org/2000/svg", "rect");
		let absolute = this.get_absolute_position();
		
		this.rect.setAttribute("x", absolute.x.toString());
		this.rect.setAttribute("y", absolute.y.toString());
		
		this.rect.setAttribute("width", this.width.toString());
		this.rect.setAttribute("height", this.height.toString());
		
		this.rect.setAttribute("fill", rect_style.fill.svg_color());
		
		if (rect_style.rx) {
			this.rect.setAttribute("rx", rect_style.rx.toString());
		}
		
		if (rect_style.ry) {
			this.rect.setAttribute("ry", rect_style.ry.toString());
		}

		this.rect.addEventListener("pointerdown", (ev) => {
			this.dragifier?.drag?.(ev);
		})
	}

	override update(): void {
		let absolute = this.get_absolute_position();

		this.rect.setAttribute("x", absolute.x.toString());
		this.rect.setAttribute("y", absolute.y.toString());
		super.update();
	}

	get_elements(): SVGElement[] {
		return [this.rect];
	}

	override set_parent(new_parent: WidgetContainer | null) {
		//Remove dragifier before new parent is set
		if (this.dragifier != null) {
			this.dragifier.stop_all_drag();
			delete this.dragifier;
		}

		super.set_parent(new_parent);
		
		//Now parent has been set so add it back
		if (new_parent != null) {
			this.setup_dragifier();
		}
	}

	setup_dragifier() {
		let svg_xparent = this.travel_up_to_type(SVGCompositor);
		if (svg_xparent != null && svg_xparent?.target_svg != this.dragifier?.capture_zone) {
			
			let handler = () => {
				let new_svg_xparent = this.travel_up_to_type(SVGCompositor);
				if (new_svg_xparent != svg_xparent) {
					svg_xparent!.changed_visual_tree.remove_listener(handler);
					this.setup_dragifier();
				}
			};

			svg_xparent.changed_visual_tree.add_listener(handler);

			this.dragifier = new Dragifier(this, svg_xparent.target_svg);
		} else {
			console.warn("rect has no SVGCompositor parent and cannot be dragged yet");
		}
	}
}