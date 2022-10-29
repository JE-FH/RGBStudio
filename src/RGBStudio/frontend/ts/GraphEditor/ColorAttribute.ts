import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { NumberInputWidget } from "../SVGCompositor/widgets/NumberInputWidget";
import { TextInputWidget } from "../SVGCompositor/widgets/TextInputWidget";
import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { RGBColor } from "../SVGCompositor/StyleHelper";
import { ColorInputWidget } from "../SVGCompositor/widgets/ColorInputWidget";
import { Json } from "../JSONRPC";
export class ColorAttribute extends GraphNodeAttribute {
	private input_widget: ColorInputWidget;
	constructor(name: string, initial_color: RGBColor, readOnly: boolean) {
		super(name);

		this.input_widget = CW(ColorInputWidget, {width: 30, initial_color: initial_color, readOnly: readOnly});
		this.visual_container.add(this.input_widget);
	}

	public get_internal_representation(): Json {
		let color = this.input_widget.ColorValue;
		return {
			r: color.r,
			g: color.g,
			b: color.b
		};
    }
}