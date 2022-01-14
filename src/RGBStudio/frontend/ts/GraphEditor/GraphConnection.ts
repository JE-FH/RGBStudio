import { GraphSourceConnector } from "./GraphSourceConnector";
import { GraphTargetConnector } from "./GraphTargetConnector";

export class GraphConnection {
	source: GraphSourceConnector;
	target: GraphTargetConnector;
	constructor(source: GraphSourceConnector, target: GraphTargetConnector) {
		this.source = source;
		this.target = target;
	}

	render(svg_target: SVGElement) {
		let line = document.createElementNS("http://www.w3.org/2000/svg", "line");
		let [x, y] = this.source.get_absolute_center_pos();
		line.setAttribute("x1", x.toString());
		line.setAttribute("y1", y.toString());

		[x, y] = this.target.get_absolute_center_pos();
		line.setAttribute("x2", x.toString());
		line.setAttribute("y2", y.toString());

		line.setAttribute("stroke", "black");
		svg_target.appendChild(line);
    }
}