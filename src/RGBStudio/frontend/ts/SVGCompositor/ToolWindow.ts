import { Widget } from "./Widget";
import { WidgetContainer } from "./WidgetContainer";
import { PaddedContainer, padding } from "./widgets/PaddedContainer";
import { TextWidget } from "./widgets/TextWidget";
import { CreateWidget2 as CW2 } from "./WidgetConstructor";
import { SVGCompositor } from "./SVGCompositor";
import { Orientation, StackPanel } from "./widgets/StackPanel";
import { Dragifier } from "./behavior/Dragifier";

export class ToolWindow {
	private container: WidgetContainer;
	private svg_target: SVGSVGElement;
	private tool_window_sp: StackPanel;
	private tool_window: PaddedContainer;

	constructor(svg_target: SVGSVGElement, container: WidgetContainer) {
		this.container = container;
		this.svg_target = svg_target;

		this.tool_window_sp = CW2(StackPanel, { orientation: Orientation.VERTICAL, item_spacing: 10 });

		this.tool_window = CW2(PaddedContainer, { padding: padding(10), background: { classes: ["debug-tool-container"] } },
			this.tool_window_sp
		);

		let tool_window_dragifier = new Dragifier(this.tool_window);

		this.tool_window.Clicked.add_listener((ev) => {
			tool_window_dragifier.drag(ev);
		});
    }

    update() {
		this.container.remove(this.tool_window);
		this.tool_window_sp.remove_all();
		this.tool_window_sp.add(
			CW2(TextWidget, { text: "Debug Window", classes: ["click-through"] })
		);

		this.add_tree(this.container, 0);
		this.container.add(this.tool_window);
    }

	private create_element_button(widget: Widget, indent: number): Widget {
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
			this.svg_target.append(...new_element);
		})

		add_thing_button.Unhovered.add_listener(() => {
			added_elements.forEach((element) => {
				this.svg_target.removeChild(element);
			})

			added_elements = [];
		})

		return CW2(PaddedContainer, { padding: padding(indent, 0, 0, 0) },
			add_thing_button
		);
	}

	private add_tree(widget: Widget, indent_level: number) {
		this.tool_window_sp.add(this.create_element_button(widget, indent_level * 10));
		if (widget instanceof WidgetContainer) {
			for (let child of widget.get_children()) {
				this.add_tree(child, indent_level + 1);
			}
		}
	}
}