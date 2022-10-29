import { RGBColor } from "../SVGCompositor/StyleHelper";
import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { BoolAttribute } from "./BoolAttribute";
import { ColorAttribute } from "./ColorAttribute";
import { GraphNode } from "./GraphNode";
import { NumberAttribute } from "./NumberAttribute";
import { SourceAttribute } from "./SourceAttribute";
import { TargetAttribute } from "./TargetAttribute";

export class ActionNode extends GraphNode {
	constructor(container: WidgetContainer, name: string, dragable: boolean) {
		super(container, "action", name, dragable);

		this.add_attribute(new SourceAttribute("source"));
		this.add_attribute(new TargetAttribute("target"));
	}
}
