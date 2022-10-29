import { CSEvent } from "../CSEvent";
import { SVGScratchArea } from "../SVGScratchArea";
import { BoundingBox, Position } from "../Widget";
import { WidgetAtom } from "../WidgetAtom";

export interface TextInputWidgetProps {
	relative_pos?: Position;
	type?: string;
	width: number;
	readOnly?: boolean;
}

export class TextInputWidget extends WidgetAtom {
	private foreign_object: SVGForeignObjectElement;
	private text_input: HTMLInputElement;
	private real_width: number;
	private real_height: number;
	public ValueChanged: CSEvent<() => void>;
	public get TextValue(): string {
		return this.text_input.value;
	}

	public set TextValue(value: string) {
		this.text_input.value = value;
	}

	constructor(props: TextInputWidgetProps) {
		super(props.relative_pos ?? {x: 0, y: 0});

		this.foreign_object = document.createElementNS("http://www.w3.org/2000/svg", "foreignObject");
		this.foreign_object.style.overflow = "visible";
		this.text_input = document.createElement("input");
		this.text_input.readOnly = props.readOnly ?? false;
		this.text_input.style.width = `${props.width}px`;
		this.foreign_object.appendChild(this.text_input);
		
		this.text_input.setAttribute("type", props.type ?? "text");

		SVGScratchArea.scratch_area.appendChild(this.foreign_object);
		let rect = this.text_input.getBoundingClientRect();
		this.real_width = rect.right - rect.left;
		this.real_height = rect.bottom - rect.top;
		SVGScratchArea.scratch_area.removeChild(this.foreign_object);

		this.ValueChanged = new CSEvent();

		this.text_input.addEventListener("input", (ev) => {
			this.ValueChanged.call();
		})
	}

	position_updated(): void {
		let abs = this.get_absolute_position();

		this.foreign_object.setAttribute("x", abs.x.toString());
		this.foreign_object.setAttribute("y", abs.y.toString());
	}

	get_elements(): SVGElement[] {
		return [this.foreign_object];
	}

	calculate_bounding_box(): BoundingBox {
		return {
			left: this.relative_pos.x,
			top: this.relative_pos.y,
			right: this.relative_pos.x + this.real_width,
			bottom: this.relative_pos.y + this.real_height
		};
	}
}