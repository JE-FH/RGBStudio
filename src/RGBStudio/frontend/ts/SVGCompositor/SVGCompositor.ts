import { Line } from "./Line";
import { Position, Widget } from "./Widget";
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
				widget.get_elements().forEach((svg_element) => {
					this._target_svg.appendChild(svg_element)
				});
			});
			this.lines.forEach((line) => {
				this._target_svg.appendChild(line.element);
			})
		});
	}
	
	update(): void {
		super.update();
	}

	get_elements(): SVGElement[] {
		return [];
	}

	add_line(line: Line): void {
		this.lines.push(line);
		this.changed_visual_tree.call();
	}
}