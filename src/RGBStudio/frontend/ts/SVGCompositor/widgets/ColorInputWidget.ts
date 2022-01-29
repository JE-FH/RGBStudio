import { RGBColor } from "../StyleHelper";
import { TextInputWidget, TextInputWidgetProps } from "./TextInputWidget";

interface FullColorInputWidgetProps extends TextInputWidgetProps {
	initial_color: RGBColor;
}

export type ColorInputWidgetProps = Omit<FullColorInputWidgetProps, "type">;


export class ColorInputWidget extends TextInputWidget {
	public get ColorValue(): RGBColor {
		return RGBColor.from_bytes(255,255,255);
	}

	public set ColorValue(value: RGBColor) {
		super.TextValue = value.svg_color();
	}

	constructor(props: ColorInputWidgetProps) {
		super({...props, type: "color"});
		this.ColorValue = props.initial_color;
	}
}