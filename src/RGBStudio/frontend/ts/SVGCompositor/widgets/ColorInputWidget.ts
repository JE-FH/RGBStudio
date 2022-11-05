import { RGBColor } from "../StyleHelper";
import { TextInputWidget, TextInputWidgetProps } from "./TextInputWidget";

interface FullColorInputWidgetProps extends TextInputWidgetProps {
	initial_color: RGBColor;
}

export type ColorInputWidgetProps = Omit<FullColorInputWidgetProps, "type">;


export class ColorInputWidget extends TextInputWidget {
	public get ColorValue(): RGBColor {
		let matched = this.TextValue.match(/#([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})/);
		if (!matched) {
			throw new Error("Invalid color format");
		}
		return RGBColor.from_bytes(Number.parseInt(matched[1], 16), Number.parseInt(matched[2], 16), Number.parseInt(matched[3], 16));
	}

	public set ColorValue(value: RGBColor) {
		super.TextValue = value.svg_color();
	}

	constructor(props: ColorInputWidgetProps) {
		super({ ...props, type: "color" });
		this.ColorValue = props.initial_color;
	}
}