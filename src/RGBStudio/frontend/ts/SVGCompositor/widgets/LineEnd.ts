import { Line } from "../Line";
import { BoundingBox, Position } from "../Widget";
import { WidgetAtom } from "../WidgetAtom";

export class LineEnd extends WidgetAtom {
	end: "1" | "2";
	line: Line;
	
	constructor(end: "1" | "2", line: Line, relative_pos?: Position) {
		super(relative_pos ?? {x: 0, y: 0});
		this.end = end;
		this.line = line;
		
		this.position_updated();
	}
	
	override position_updated(): void {
		let absolute = this.get_absolute_position();
		
		this.line.element.setAttribute("x" + this.end, (absolute.x).toString());
		this.line.element.setAttribute("y" + this.end, (absolute.y).toString());
	}
	
	override get_elements(): SVGElement[] {
		//Line is added on top by SVGCompositor so we return nothing
		return [];
	}

	calculate_bounding_box(): BoundingBox {
		return {
			left: this.relative_pos.x,
			top: this.relative_pos.y,
			right: this.relative_pos.x,
			bottom: this.relative_pos.y
		};
	}
}