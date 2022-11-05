import { Line } from "./Line";
import { BoundingBox, Position, Widget } from "./Widget";
import { WidgetContainer } from "./WidgetContainer";

export class SVGCompositor extends WidgetContainer {
	private _target_svg: SVGSVGElement;
	private lines: Line[];
	
	public get target_svg() {
		return this._target_svg;
	}
	
	constructor(target_svg: SVGSVGElement) {
		super({x: 0, y: 0});
		
		this._target_svg = target_svg;
		
		this.lines = [];
		
		this.changed_visual_tree.add_listener(() => {
			while (this._target_svg.firstChild) {
				this._target_svg.removeChild(this._target_svg.lastChild!);
			}
			this.tree_walk((widget) => {
				if (widget == this)
				return;
				widget.get_elements().forEach((svg_element) => {
					this._target_svg.appendChild(svg_element)
				});
			});
			this.lines.forEach((line) => {
				this._target_svg.appendChild(line.element);
			})
		});
	}
	
	position_updated(): void {
		super.position_updated();
	}
	
	get_elements(): SVGElement[] {
		return [this._target_svg];
	}

	calculate_bounding_box(): BoundingBox {
		let parent_absolute = this.parent?.get_absolute_position?.() ?? {x: 0, y: 0};
		return {
			left: parent_absolute.x,
			top: parent_absolute.y,
			right: parent_absolute.x + this._target_svg.clientWidth,
			bottom: parent_absolute.y + this._target_svg.clientHeight
		};
	}

	add_line(line: Line): void {
		this.lines.push(line);
		this.changed_visual_tree.call();
	}
}