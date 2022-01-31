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

declare global {
	interface Window {
		chrome: {
			webview: {
				postMessage: (message: string) => void;
			}
		}
	}
}

function main() {
	//HelloWorldBinding();

	SVGScratchArea.setup(document.getElementById("scratch-pad")! as unknown as SVGElement);

	let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;
	let svg_compositor = new SVGCompositor(svg_target);

	let graph_node = new GraphNode(svg_compositor, "hello world!");

	graph_node.add_attribute(new NumberAttribute("number", 1));
	graph_node.add_attribute(new ColorAttribute("color", RGBColor.from_bytes(255, 0, 0)));
	graph_node.add_attribute(new SourceAttribute("source"));
	graph_node.add_attribute(new TargetAttribute("target"));

	function create_element_button(widget: Widget, indent: number): Widget {
		let add_thing_button = CW2(PaddedContainer, { padding: padding(5), background: { classes: ["debug-button"] } },
			CW2(TextWidget, { text: (widget as any).constructor.name, classes: ["tool-window-text"] })
		);

		add_thing_button.Clicked.add_listener(() => {
			console.log(widget);
		});
		let added_elements: SVGRectElement[] = [];
		add_thing_button.Hovered.add_listener(() => {
			let new_element = widget.create_bounding_box_rect();
			added_elements = added_elements.concat(new_element);
			svg_target.append(...new_element);
		})

		add_thing_button.Unhovered.add_listener(() => {
			added_elements.forEach((element) => {
				svg_target.removeChild(element);
			})

			added_elements = [];
		})

		return CW2(PaddedContainer, { padding: padding(indent, 0, 0, 0) },
			add_thing_button
		);
	}

	let tool_window_sp = CW2(StackPanel, { orientation: Orientation.VERTICAL, item_spacing: 10 },
		CW2(TextWidget, { text: "Debug Window", classes: ["click-through"] })
	);

	function add_tree(widget: Widget, indent_level: number) {
		tool_window_sp.add(create_element_button(widget, indent_level * 10));
		if (widget instanceof WidgetContainer) {
			for (let child of widget.get_children()) {
				add_tree(child, indent_level + 1);
			}
		}
	}

	add_tree(svg_compositor, 0);


	let tool_window =
		CW2(PaddedContainer, { padding: padding(10), background: { classes: ["debug-tool-container"] } },
			tool_window_sp
		);

	svg_compositor.add(tool_window);

	let tool_window_dragifier = new Dragifier(tool_window);

	tool_window.Clicked.add_listener((ev) => {
		tool_window_dragifier.drag(ev);
	});
}

window.addEventListener("load", () => {
	main();
})