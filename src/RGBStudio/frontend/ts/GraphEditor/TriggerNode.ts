import { GraphNode } from "./GraphNode";
import { GraphSourceConnector } from "./GraphSourceConnector";
import { NumberAttribute } from "./NumberAttribute";
import { TriggerConnector } from "./TriggerConnector";

export class TriggerNode extends GraphNode {
	constructor(name: string, x: number, y: number, width: number, height: number, ) {
		super(name, x, y, width, height);
		this.add_attribute(new NumberAttribute("key code", 12));
		this.add_source_node(new GraphSourceConnector(this, "trigger", new TriggerConnector()));
	}

	override render(target: SVGElement) {
		let g = document.createElementNS("http://www.w3.org/2000/svg", "g");

		let inner_svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
		g.appendChild(inner_svg);

		inner_svg.setAttribute("x", this.x.toString());
		inner_svg.setAttribute("y", this.y.toString());
		inner_svg.setAttribute("width", (this.width + 20).toString());
		inner_svg.setAttribute("width", (this.height + 20).toString());


		let rect = document.createElementNS("http://www.w3.org/2000/svg", "rect");
		inner_svg.appendChild(rect);

		rect.setAttribute("x", "10");
		rect.setAttribute("y", "10");
		rect.setAttribute("width", this.width.toString());
		rect.setAttribute("height", this.height.toString());

		rect.setAttribute("fill", "#ff0000");

		let text = document.createElementNS("http://www.w3.org/2000/svg", "text");
		inner_svg.appendChild(text);
		text.appendChild(document.createTextNode(this.name));
		text.setAttribute("x", (this.width/2 + 10).toString());
		text.setAttribute("y", "15");
		text.setAttribute("alignment-baseline", "hanging");
		text.setAttribute("text-anchor", "middle");
		text.classList.add("something");

		super.render_connectors(inner_svg, 10, 10);
		target.appendChild(g);
		return;
    }
}