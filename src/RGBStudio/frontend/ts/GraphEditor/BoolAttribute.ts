import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { CheckboxInputWidget } from "../SVGCompositor/widgets/CheckboxInputWidget";
export class BoolAttribute extends GraphNodeAttribute {
	constructor(name: string, initial_value: boolean) {
		super(name);

		let input_widget = CW(CheckboxInputWidget, { initial_value: initial_value});
		this.visual_container.add(input_widget);
	}
}