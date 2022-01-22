import { LineEnd } from "./widgets/LineEnd";
import { RGBColor } from "./StyleHelper";
import { Position } from "./Widget";

export interface LineStyle {
	stroke: RGBColor;
}

export class Line {
	private _element: SVGLineElement;
	private _start: LineEnd;
	private _end: LineEnd;
	
	public get start() {
		return this._start;
	}
	
	public get end() {
		return this._end;
	}

	public get element() {
		return this._element;
	}

	constructor(from: Position, to: Position, line_style: LineStyle) {
		this._element = document.createElementNS("http://www.w3.org/2000/svg", "line");
		this._element.setAttribute("stroke", line_style.stroke.svg_color());
		this._start = new LineEnd("1", this, from);
		this._end = new LineEnd("2", this, to);
	}
}