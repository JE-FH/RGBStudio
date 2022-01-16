import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { GraphSourceConnector } from "./GraphSourceConnector";
import { GraphTargetConnector } from "./GraphTargetConnector";

export abstract class GraphNode {
	name: string;
	x: number;
	y: number;
	width: number;
	height: number;
	sources: GraphSourceConnector[];
	targets: GraphTargetConnector[];
	attributes: GraphNodeAttribute[];
	render_target: SVGElement;

	constructor(name: string, x: number, y: number, width: number, height: number) {
		this.name = name;
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		this.sources = [];
		this.targets = [];
		this.attributes = [];
		this.render_target = document.createElementNS("http://www.w3.org/2000/svg", "svg");
	}

	abstract render(target: SVGElement): void;

	protected render_connectors(render_target: SVGElement, offset_x: number, offset_y: number) {
		this.render_target = render_target;
		let current_offset = 0;
		for (let target of this.targets) {
			target.set_relative_position(0, current_offset);
			let connector = target.render(offset_x, offset_y);
			current_offset += 20;
			render_target.appendChild(connector);
		}
		current_offset = 0;
		for (let source of this.sources) {
			source.set_relative_position(this.width, current_offset);
			let connector = source.render(offset_x, offset_y);
			current_offset += 20;
			render_target.appendChild(connector);
		}
	}

	protected render_node_block(render_target: SVGElement, offset_x: number, offset_y: number) {
		let rect = document.createElementNS("http://www.w3.org/2000/svg", "rect");
		render_target.appendChild(rect);
		
		rect.setAttribute("x", offset_x.toString());
		rect.setAttribute("y", offset_y.toString());
		rect.setAttribute("width", this.width.toString());
		rect.setAttribute("height", this.height.toString());

		rect.setAttribute("fill", "#D9D9D9");

		let text = document.createElementNS("http://www.w3.org/2000/svg", "text");
		render_target.appendChild(text);
		text.appendChild(document.createTextNode(this.name));
		text.setAttribute("x", (offset_x + this.width/2).toString());
		text.setAttribute("y", (offset_y + 5).toString());
		text.setAttribute("alignment-baseline", "hanging");
		text.setAttribute("text-anchor", "middle");
		text.classList.add("something");
	}

	protected add_attribute(attribute: GraphNodeAttribute) {
		this.attributes.push(attribute);
	}

	protected add_source_node(source_connector: GraphSourceConnector) {
		this.sources.push(source_connector);
	}

	protected add_target_node(target_connector: GraphTargetConnector) {
		this.targets.push(target_connector);
	}
}