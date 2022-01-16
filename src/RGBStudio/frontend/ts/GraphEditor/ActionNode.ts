import ConnectorTypeRepository from "./ConnectorTypeRepository";
import { GraphNode } from "./GraphNode";
import { GraphSourceConnector } from "./GraphSourceConnector";
import "./ActionConnector";
import { GraphTargetConnector } from "./GraphTargetConnector";

export class ActionNode extends GraphNode {
	constructor(name: string, x: number, y: number, width: number, height: number, ) {
		super(name, x, y, width, height);
		this.add_target_node(new GraphTargetConnector(this, "trigger", ConnectorTypeRepository.get_connector("TriggerConnector")));
		this.add_source_node(new GraphSourceConnector(this, "action", ConnectorTypeRepository.get_connector("ActionConnector")));
	}

	override render(target: SVGElement) {
		let g = document.createElementNS("http://www.w3.org/2000/svg", "g");

		let inner_svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
		g.appendChild(inner_svg);

		inner_svg.setAttribute("x", (this.x - 10).toString());
		inner_svg.setAttribute("y", (this.y - 10).toString());
		inner_svg.setAttribute("width", (this.width + 20).toString());
		inner_svg.setAttribute("width", (this.height + 20).toString());

		this.render_node_block(inner_svg, 10, 10);

		super.render_connectors(inner_svg, 10, 10);
		target.appendChild(g);
		return;
    }
}