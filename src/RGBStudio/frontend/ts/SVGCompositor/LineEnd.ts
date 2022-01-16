import { Line } from "./Line";
import { Position } from "./Widget";
import { WidgetAtom } from "./WidgetAtom";

export class LineEnd extends WidgetAtom {
	end: "1" | "2";
	line: Line;

	constructor(end: "1" | "2", line: Line, relative_pos: Position) {
		super(relative_pos);
		this.end = end;
		this.line = line;

		this.update();
	}
	
	override update(): void {
		let absolute = this.get_absolute_position();
		
		this.line.element.setAttribute("x" + this.end, (absolute.x + this.relative_pos.x).toString());
		this.line.element.setAttribute("y" + this.end, (absolute.y + this.relative_pos.y).toString());
	}

	override get_elements(): SVGElement[] {
		//Line is added on top by SVGCompositor so we return nothing
		return [];
	}
}