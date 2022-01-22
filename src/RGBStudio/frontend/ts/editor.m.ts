import { Dragifier } from "./SVGCompositor/behavior/Dragifier";
import { RectangleContainer } from "./SVGCompositor/widgets/RectangleContainer";
import { RGBColor } from "./SVGCompositor/StyleHelper";
import { SVGCompositor } from "./SVGCompositor/SVGCompositor";
import { TextWidget } from "./SVGCompositor/widgets/TextWidget";
import { SVGScratchArea } from "./SVGCompositor/SVGScratchArea";
import { Orientation, StackPanel } from "./SVGCompositor/widgets/StackPanel";
import { PaddedContainer, padding } from "./SVGCompositor/widgets/PaddedContainer";
import { Widget } from "./SVGCompositor/Widget";
import { FlexBox } from "./SVGCompositor/widgets/FlexBox";
import { Circle } from "./SVGCompositor/widgets/Circle";
import { CreateWidget as CW} from "./SVGCompositor/WidgetConstructor";
import { Line } from "./SVGCompositor/Line";
import { WidgetContainer } from "./SVGCompositor/WidgetContainer";

SVGScratchArea.setup(document.getElementById("scratch-pad")! as unknown as SVGElement);

let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;

let svg_compositor = new SVGCompositor(svg_target);

let line = new Line({x: 5, y: 5}, {x: 5, y: 5}, {stroke: RGBColor.from_bytes(0, 0, 0)});

let keypress_trigger = 
CW(RectangleContainer, [padding(0), {fill: RGBColor.from_bytes(0xD9, 0xD9, 0xD9), classes: ["dragable"]}, {x: 100, y: 100}], [
	CW(StackPanel, [Orientation.VERTICAL, 0], [
		CW(RectangleContainer, [padding(5), {fill: RGBColor.from_bytes(255, 50, 50), classes: ["node-title-container"]}], [
			CW(TextWidget, ["Key press (trigger)", {classes: ["node-title"]}])
		]),
		CW(PaddedContainer, [padding(10)], [
			CW(StackPanel, [Orientation.VERTICAL, 5], [
				CW(FlexBox, [10], [
					CW(TextWidget, ["Key code", {classes: ["attribute-text"]}]),
					CW(TextWidget, ["64 (left arrow)", {classes: ["attribute-text"]}])
				]),
				CW(FlexBox, [10], [
					CW(TextWidget, ["Source connection", {classes: ["attribute-text"]}]),
					CW(Circle, [5, {fill: RGBColor.from_bytes(0xdd, 50, 50)}, {x: 0, y: 6}], [
						line.start
					])
				])
			])
		])
	]),
]);

let keypress_trigger_dragifier = new Dragifier(keypress_trigger);
keypress_trigger.Clicked.add_listener((ev) => {
	keypress_trigger_dragifier.drag(ev);
});

svg_compositor.add(keypress_trigger);


let action = 
CW(RectangleContainer, [padding(0), {fill: RGBColor.from_bytes(0xD9, 0xD9, 0xD9), classes: ["dragable"]}, {x: 200, y: 100}], [
	CW(StackPanel, [Orientation.VERTICAL, 0], [
		CW(RectangleContainer, [padding(5), {fill: RGBColor.from_bytes(50, 255, 50), classes: ["node-title-container"]}], [
			CW(TextWidget, ["Left key pressed (action)", {classes: ["node-title"]}])
		]),
		CW(PaddedContainer, [padding(10)], [
			CW(StackPanel, [Orientation.VERTICAL, 5], [
				CW(FlexBox, [10], [
					CW(Circle, [5, {fill: RGBColor.from_bytes(0xdd, 50, 50)}, {x: 0, y: 6}], [
						line.end
					]),
					CW(TextWidget, ["Action", {classes: ["attribute-text"]}])
				]),
				CW(FlexBox, [10], [
					CW(TextWidget, ["Trigger", {classes: ["attribute-text"]}]),
					CW(Circle, [5, {fill: RGBColor.from_bytes(50, 0xdd, 50)}, {x: 0, y: 6}])
				])
			])
		])
	])
]);

let action_dragifier = new Dragifier(action);
action.Clicked.add_listener((ev) => {
	action_dragifier.drag(ev);
});

svg_compositor.add(action);

svg_compositor.add_line(line);


function create_toolwindow_button(text: string, indent: number, handler: (ev: PointerEvent) => void): Widget {
	let add_thing_button = CW(RectangleContainer, [padding(5), {fill: RGBColor.from_bytes(0, 0, 0)}], [
		CW(TextWidget, [text, {classes: ["tool-window-text"]}])
	]);

	add_thing_button.Clicked.add_listener(handler);

	return CW(StackPanel, [Orientation.HORIZONTAL, 0], [
		CW(PaddedContainer, [padding(indent, 0, 0, 0)]),
		add_thing_button
	]);
}

let tool_window_sp = CW(StackPanel, [Orientation.VERTICAL, 10], [
	CW(TextWidget, ["Debug Window", {classes: ["click-through"]}])
]);

function add_tree(widget: Widget, indent_level: number) {
	tool_window_sp.add(create_toolwindow_button((widget as any).constructor.name, indent_level * 10, () => {
		console.log(widget);
	}));
	if (widget instanceof WidgetContainer) {
		for (let child of widget.get_children()) {
			add_tree(child, indent_level + 1);
		}
	}
}

add_tree(svg_compositor, 0);


let tool_window = 
CW(RectangleContainer, [padding(10), {fill: RGBColor.from_bytes(0xd9, 0xd9, 0xd9)}], [
	tool_window_sp
]);

svg_compositor.add(tool_window);

let tool_window_dragifier = new Dragifier(tool_window);

tool_window.Clicked.add_listener((ev) => {
	tool_window_dragifier.drag(ev);
});
/*
let graph_model = new GraphModel();

let a = new TriggerNode("hello", 10, 10, 100, 100);

graph_model.add_node(a);

let b = new TriggerNode("hello2", 10, 150, 100, 100);

graph_model.add_node(b);

let c = new ActionNode("bing bong", 140, 30, 100, 100);

graph_model.add_node(c);


graph_model.create_connection(b.sources[0], c.targets[0]);
graph_model.create_connection(a.sources[0], c.targets[0]);

//We do get the SVGSVGElement even though we shouldnt but who cares
let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;

graph_model.render(svg_target);
*/
