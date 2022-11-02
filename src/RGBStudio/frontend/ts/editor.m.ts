
import { SVGCompositor } from "./SVGCompositor/SVGCompositor";
import { SVGScratchArea } from "./SVGCompositor/SVGScratchArea";
import { JSONRPC } from "./JSONRPC";
import { WebViewConnection } from "./WebViewConnection";
import { ToolWindow } from "./SVGCompositor/ToolWindow";
import { GraphEditor } from "./GraphEditor/GraphEditor";
import { RGBStudioAPI } from "./RGBStudioAPI";

async function main() {
	SVGScratchArea.setup(document.getElementById("scratch-pad")! as unknown as SVGElement);

	let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;
	let svg_compositor = new SVGCompositor(svg_target);
	let tool_window = new ToolWindow(svg_target, svg_compositor);

	tool_window.update();


	let api = new RGBStudioAPI();

	let graph_editor = new GraphEditor(svg_compositor, tool_window, api);

	api.OnAddedTrigger.add_listener((addedTrigger) => {
		graph_editor.add_trigger_type(addedTrigger);
    })

	await api.Ready();
}

window.addEventListener("load", () => {
	main();
})