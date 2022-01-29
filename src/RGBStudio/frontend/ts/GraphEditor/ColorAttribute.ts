import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { NumberInputWidget } from "../SVGCompositor/widgets/NumberInputWidget";
import { TextInputWidget } from "../SVGCompositor/widgets/TextInputWidget";
import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { RGBColor } from "../SVGCompositor/StyleHelper";
import { ColorInputWidget } from "../SVGCompositor/widgets/ColorInputWidget";
export class ColorAttribute extends GraphNodeAttribute {
	constructor(name: string, initial_color: RGBColor) {
		super(name);

		let input_widget = CW(ColorInputWidget, {width: 30, initial_color: initial_color});
		this.visual_container.add(input_widget);
	}
}