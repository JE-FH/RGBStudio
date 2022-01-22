import { CSEvent } from "../CSEvent";
import { SVGScratchArea } from "../SVGScratchArea";
import { Resizing } from "../trait/Resizing";
import { BoundingBox, Position } from "../Widget";
import { WidgetAtom } from "../WidgetAtom";

export interface TextStyle {
	classes?: string[];
}

export class TextWidget 
	extends WidgetAtom
	implements Resizing
{
	private text_element: SVGTextElement;
	private text_node: Text;
	private _text_offset: Position;
	private _width: number;
	private _height: number;
	
	public set text(value: string) {
		if (this.text_node.data == value) {
			return;
		}

		this.text_node.data = value;

		let new_bbox = this.calculate_bbox();
		this._text_offset.x = new_bbox.left;
		this._text_offset.y = new_bbox.top;
		this._width = new_bbox.right - new_bbox.left;
		this._height = new_bbox.bottom - new_bbox.top;


		this._Resized.call();
		this.position_updated();
	}

	public get text() {
		return this.text_node.data;
	}

	constructor(text: string, style: TextStyle, relative_pos?: Position) {
		super(relative_pos ?? {x: 0, y: 0});
		this._text_offset = {x: 0, y: 0};
		this.text_node = document.createTextNode("");
		this.text_element = document.createElementNS("http://www.w3.org/2000/svg", "text");
		this._Resized = new CSEvent();
		this._width = 0;
		this._height = 0;

		if (style.classes) {
			style.classes.forEach((_class) => {
				this.text_element.classList.add(_class);
			})
		}

		this.text_element.appendChild(this.text_node);

		this.text = text;
		this.position_updated();
	}

	position_updated(): void {
		let absolute = this.get_absolute_position();

		this.text_element.setAttribute("x", (absolute.x - this._text_offset.x).toString());
		this.text_element.setAttribute("y", (absolute.y - this._text_offset.y).toString());
	}

	get_elements(): SVGElement[] {
		return [this.text_element];
	}

	calculate_bounding_box(): BoundingBox {
		return {
			left: this.relative_pos.x,
			top: this.relative_pos.y,
			right: this.relative_pos.x + this._width,
			bottom: this.relative_pos.y + this._height
		};
	}

	private calculate_bbox(): BoundingBox {
		let _bbox = this.text_element.getBBox({
			fill: true,
			stroke: true
		});

		let bbox: BoundingBox;

		if (_bbox.width + _bbox.height == 0 && this.text.length != 0) {
			bbox = this.scratch_area_calculate_bbox();
		} else {
			let parent_absolute = this.parent?.get_absolute_position?.() ?? {x: 0, y: 0};
			
			bbox = {
				left: _bbox.x - parent_absolute.x,
				top: _bbox.y - parent_absolute.y,
				right: _bbox.x + _bbox.width - parent_absolute.x,
				bottom: _bbox.y + _bbox.height - parent_absolute.y
			};
		}
		return bbox;
	}

	private scratch_area_calculate_bbox(): BoundingBox {
		let parent = this.text_element.parentNode;
		let next_sibling = this.text_element.nextSibling;

		if (parent)
			parent.removeChild(this.text_element);


		SVGScratchArea.scratch_area.appendChild(this.text_element);

		let bbox = this.text_element.getBBox({
			fill: true,
			stroke: true
		});

		SVGScratchArea.scratch_area.removeChild(this.text_element);

		if (parent)
			parent.insertBefore(this.text_element, next_sibling);

		return {
			left: bbox.x,
			top: bbox.y,
			right: bbox.x + bbox.width,
			bottom: bbox.y + bbox.height
		};
	}

	//implement Resizing
	readonly __RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true = true;
	_Resized: CSEvent<() => void>;
	get Resized(): CSEvent<() => void> {
		return this._Resized;
	}
}