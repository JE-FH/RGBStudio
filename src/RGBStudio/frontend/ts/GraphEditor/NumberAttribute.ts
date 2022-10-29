import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { NumberInputWidget } from "../SVGCompositor/widgets/NumberInputWidget";
import { TextInputWidget } from "../SVGCompositor/widgets/TextInputWidget";
import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { Json } from "../JSONRPC";
export class NumberAttribute extends GraphNodeAttribute {
	private input_widget: NumberInputWidget;
	constructor(name: string, initial_value: number, readOnly: boolean) {
		super(name);

		this.input_widget = CW(NumberInputWidget, { width: 60, initial_number: 10, readOnly: readOnly});
		this.visual_container.add(this.input_widget);
	}

	public get_internal_representation(): Json {
		return this.input_widget.NumberValue;
    }

}