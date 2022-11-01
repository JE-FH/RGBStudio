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
import { Call, JSONRPC } from "./JSONRPC";
import { WebViewConnection } from "./WebViewConnection";
import { BoolAttribute } from "./GraphEditor/BoolAttribute";
import { ToolWindow } from "./SVGCompositor/ToolWindow";
import { TriggerNode, TriggerType } from "./GraphEditor/TriggerNode";
import { GraphEditor } from "./GraphEditor/GraphEditor";



interface AddedTriggerCall extends Call<any> {
	method: "added_trigger";
	param: TriggerType;
}

async function main() {
	SVGScratchArea.setup(document.getElementById("scratch-pad")! as unknown as SVGElement);

	let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;
	let svg_compositor = new SVGCompositor(svg_target);
	let tool_window = new ToolWindow(svg_target, svg_compositor);

	tool_window.update();

	let graph_editor = new GraphEditor(svg_compositor, tool_window);


	let rpc = new JSONRPC(new WebViewConnection());
	rpc.on_call.add_listener((call_data) => {
		if (call_data.method == "added_trigger") {
			let specific_data = call_data as unknown as AddedTriggerCall;
			graph_editor.add_trigger_type(specific_data.param);
		}
	});


	console.log("sent ready signal");
}

window.addEventListener("load", () => {
	main();
})