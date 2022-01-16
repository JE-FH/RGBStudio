import ConnectorTypeRepository from "./ConnectorTypeRepository";
import { GraphNode } from "./GraphNode";
import { GraphSourceConnector } from "./GraphSourceConnector";
import { NumberAttribute } from "./NumberAttribute";
import "./TriggerConnector";

export class TriggerNode extends GraphNode {
	start_relative_x: number;
	start_relative_y: number;

	constructor(name: string, x: number, y: number, width: number, height: number) {
		super(name, x, y, width, height);
		this.add_attribute(new NumberAttribute("key code", 12));
		this.add_source_node(new GraphSourceConnector(this, "triggerin", ConnectorTypeRepository.get_connector("TriggerConnector")));
		this.start_relative_x = 0;
		this.start_relative_y = 0;
	}

	override render(target: SVGElement) {
		let g = document.createElementNS("http://www.w3.org/2000/svg", "g");

		let inner_svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
		g.appendChild(inner_svg);
		inner_svg.addEventListener("mousedown", this.mousedown.bind(this));
		inner_svg.setAttribute("x", (this.x - 10).toString());
		inner_svg.setAttribute("y", (this.y - 10).toString());
		inner_svg.setAttribute("width", (this.width + 20).toString());
		inner_svg.setAttribute("width", (this.height + 20).toString());

		this.render_node_block(inner_svg, 10, 10);

		super.render_connectors(inner_svg, 10, 10);
		target.appendChild(g);
		return;
	}

	mousedown(ev: MouseEvent) {
		let bounding_rect = this.render_target.getBoundingClientRect();
		
		this.start_relative_x = ev.x - bounding_rect.left;
		this.start_relative_y = ev.y - bounding_rect.top;

		document.addEventListener("mousemove", this.mousemove.bind(this));
	}

	mousemove(ev: MouseEvent) {
		let bounding_rect = this.render_target.getBoundingClientRect();

		let new_x = ev.x - this.start_relative_x;
		let new_y = ev.y - this.start_relative_y;

		this.render_target.setAttribute("x", new_x.toString());
		this.render_target.setAttribute("y", new_y.toString());
	}
}