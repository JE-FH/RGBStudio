import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { CheckboxInputWidget } from "../SVGCompositor/widgets/CheckboxInputWidget";
import { Json } from "../JSONRPC";
export class BoolAttribute extends GraphNodeAttribute {
	private input_widget: CheckboxInputWidget;
	constructor(name: string, initial_value: boolean, readOnly: boolean) {
		super(name);

		this.input_widget = CW(CheckboxInputWidget, { initial_value: initial_value, readOnly: readOnly });
		this.visual_container.add(this.input_widget);
	}
    public get_internal_representation(): string {
		return this.input_widget.Value ? "true" : "false";
    }
}