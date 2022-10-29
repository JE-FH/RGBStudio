import { RGBColor } from "../SVGCompositor/StyleHelper";
import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { BoolAttribute } from "./BoolAttribute";
import { ColorAttribute } from "./ColorAttribute";
import { GraphNode } from "./GraphNode";
import { NumberAttribute } from "./NumberAttribute";
import { SourceAttribute } from "./SourceAttribute";

interface TriggerField {
	name: string;
	required: boolean;
	type: string;
}

export interface TriggerType {
	name: string;
	fields: { [key: string]: TriggerField };
}

export class TriggerNode extends GraphNode {
	constructor(container: WidgetContainer, name: string, dragable: boolean, readOnly: boolean) {
        super(container, "trigger", name, dragable);

        this.add_attribute(new SourceAttribute("trigger"));
	}

	static from_trigger_type(container: WidgetContainer, name: string, trigger_type: TriggerType, dragable: boolean, readOnly: boolean): TriggerNode {
		let rv = new TriggerNode(container, name, dragable, readOnly);

		for (let [field_name, field] of Object.entries(trigger_type.fields)) {
			if (field.type == "Integer") {
				rv.add_attribute(new NumberAttribute(field.name, 1, readOnly));
			} else if (field.type == "Number") {
				rv.add_attribute(new NumberAttribute(field.name, 1, readOnly));
			} else if (field.type == "RGBColor") {
				rv.add_attribute(new ColorAttribute(field.name, RGBColor.from_bytes(255, 255, 255), readOnly));
			} else if (field.type == "Bool") {
				rv.add_attribute(new BoolAttribute(field.name, false, readOnly));
			} else {
				console.log(`Unknown attribute type for ${field_name}`, field);
			}
		}
		return rv;
    }
}
