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
	
	constructor(name: string, x: number, y: number, width: number, height: number) {
		this.name = name;
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		this.sources = [];
		this.targets = [];
		this.attributes = [];
	}

	abstract render(target: SVGElement): void;

	render_connectors(render_target: SVGElement, offset_x: number, offset_y: number) {
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