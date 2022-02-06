import { Dragifier } from "./SVGCompositor/behavior/Dragifier";
import { RGBColor } from "./SVGCompositor/StyleHelper";
import { SVGCompositor } from "./SVGCompositor/SVGCompositor";
import { TextWidget } from "./SVGCompositor/widgets/TextWidget";
import { SVGScratchArea } from "./SVGCompositor/SVGScratchArea";
import { Orientation, StackPanel } from "./SVGCompositor/widgets/StackPanel";
import { PaddedContainer, padding } from "./SVGCompositor/widgets/PaddedContainer";
import { Widget } from "./SVGCompositor/Widget";
import { FlexBox } from "./SVGCompositor/widgets/FlexBox";
import { Circle } from "./SVGCompositor/widgets/Circle";
import { CreateWidget2 as CW2} from "./SVGCompositor/WidgetConstructor";
import { Line } from "./SVGCompositor/Line";
import { WidgetContainer } from "./SVGCompositor/WidgetContainer";
import { GraphNode } from "./GraphEditor/GraphNode";
import { NumberAttribute } from "./GraphEditor/NumberAttribute";
import { ColorAttribute } from "./GraphEditor/ColorAttribute";
import { SourceAttribute } from "./GraphEditor/SourceAttribute";
import { TargetAttribute } from "./GraphEditor/TargetAttribute";
import { Call, JSONRPC } from "./JSONRPC";
import { WebViewConnection } from "./WebViewConnection";
import { BoolAttribute } from "./GraphEditor/BoolAttribute";
import { ToolWindow } from "./SVGCompositor/ToolWindow";

interface TriggerField {
	name: string;
	required: boolean;
	type: string;
}

interface AddedTriggerCall extends Call<any> {
	method: "added_trigger";
	param: {
		name: string;
		fields: { [key: string]: TriggerField };
	};
}

async function main() {
	SVGScratchArea.setup(document.getElementById("scratch-pad")! as unknown as SVGElement);

	let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;
	let svg_compositor = new SVGCompositor(svg_target);

	let graph_node = new GraphNode(svg_compositor, "hello world!");

	graph_node.add_attribute(new NumberAttribute("number", 1));
	graph_node.add_attribute(new ColorAttribute("color", RGBColor.from_bytes(255, 0, 0)));
	graph_node.add_attribute(new SourceAttribute("source"));
	graph_node.add_attribute(new TargetAttribute("target"));

	let tool_window = new ToolWindow(svg_target, svg_compositor);

	tool_window.update();

	let rpc = new JSONRPC(new WebViewConnection());
	rpc.on_call.add_listener((call_data) => {
		if (call_data.method == "added_trigger") {
			let specific_data = call_data as unknown as AddedTriggerCall;
			console.log(specific_data);
			let new_graph_node = new GraphNode(svg_compositor, specific_data.param.name);
			for (let [field_name, field] of Object.entries(specific_data.param.fields)) {
				if (field.type == "Integer") {
					new_graph_node.add_attribute(new NumberAttribute(field.name, 1));
				} else if (field.type == "Number") {
					new_graph_node.add_attribute(new NumberAttribute(field.name, 1));
				} else if (field.type == "RGBColor") {
					new_graph_node.add_attribute(new ColorAttribute(field.name, RGBColor.from_bytes(255, 255, 255)));
				} else if (field.type == "Bool") {
					new_graph_node.add_attribute(new BoolAttribute(field.name, false));
				} else {
					console.log(`Unknown attribute type for ${field_name}`, field);
                }
			}
			tool_window.update();
		}
	});

	await rpc.dispatch_call("ready", {});

	console.log("sent ready signal");
}

window.addEventListener("load", () => {
	main();
})