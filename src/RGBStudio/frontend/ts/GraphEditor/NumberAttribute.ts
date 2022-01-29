import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { NumberInputWidget } from "../SVGCompositor/widgets/NumberInputWidget";
import { TextInputWidget } from "../SVGCompositor/widgets/TextInputWidget";
import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
export class NumberAttribute extends GraphNodeAttribute {
	constructor(name: string, initial_value: number) {
		super(name);

		let input_widget = CW(NumberInputWidget, {width: 60, initial_number: 10});
		this.visual_container.add(input_widget);
	}
}