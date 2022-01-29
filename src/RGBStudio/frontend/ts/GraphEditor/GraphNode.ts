import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { PaddedContainer, padding } from "../SVGCompositor/widgets/PaddedContainer";
import { Orientation, StackPanel } from "../SVGCompositor/widgets/StackPanel";
import { TextWidget } from "../SVGCompositor/widgets/TextWidget";
import { CreateWidget as CW, CreateWidget2 as CW2} from "../SVGCompositor/WidgetConstructor";
import { FlexBox } from "../SVGCompositor/widgets/FlexBox";
import { Circle } from "../SVGCompositor/widgets/Circle";
import { Dragifier } from "../SVGCompositor/behavior/Dragifier";
import { GraphNodeAttribute } from "./GraphNodeAttribute";

export class GraphNode {
	private container: WidgetContainer;
	private root_widget: PaddedContainer;
	private title_text: TextWidget;
	private attribute_container: StackPanel;
	private _name: string = "";
	private attributes: GraphNodeAttribute[];

	public get name(): string {
		return this._name;
	}
	public set name(value: string) {
		this._name = value;
		this.name_updated();
	}

	constructor(container: WidgetContainer, name: string) {
		this.attributes = [];
		this.container = container;

		this.title_text = CW2(TextWidget, {text: "", classes: ["node-title"]});

		this.attribute_container = CW2(StackPanel, {orientation: Orientation.VERTICAL, item_spacing: 10});

		this.root_widget = CW2(PaddedContainer, {
				padding: padding(0), 
				relative_position: {x: 100, y: 100},
				background: {classes: ["dragable", "node"]}
			},
			CW2(StackPanel, {orientation: Orientation.VERTICAL, item_spacing: 0},
				CW2(PaddedContainer, {
						padding: padding(5), 
						background: {classes: ["node-title-container", "trigger"]}
					},
					this.title_text
				),
				CW2(PaddedContainer, {
						padding: padding(5)
					},
					this.attribute_container
				)
			)
		);
		
		let dragifier = new Dragifier(this.root_widget);
		this.root_widget.Clicked.add_listener((ev) => {
			dragifier.drag(ev);
		})

		this.container.add(this.root_widget);

		this.name = name;
	}

	protected name_updated() {
		this.title_text.text = `${this.name}`;
	}

	public add_attribute(attr: GraphNodeAttribute) {
		this.attributes.push(attr);
		this.attribute_container.add(attr.visual_container);
	}
}