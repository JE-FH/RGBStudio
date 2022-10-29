import { Circle } from "../SVGCompositor/widgets/Circle";
import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { Json } from "../JSONRPC";
export class SourceAttribute extends GraphNodeAttribute {
    public get_internal_representation(): Json {
        throw new Error("Method not implemented.");
    }
	constructor(name: string) {
		super(name);
		
		let circle_widget = CW(Circle, {radius: 5, relative_pos: {x: 0, y: 5}, classes: ["trigger-connector"]});
		this.visual_container.add(circle_widget);
	}
}