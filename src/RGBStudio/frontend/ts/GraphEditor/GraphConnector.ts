import {ConnectorType} from "./ConnectorType";
import {GraphConnection} from "./GraphConnection";
import { GraphNode } from "./GraphNode";

export abstract class GraphConnector {
	name: string;
	connection_type: ConnectorType;
	connections: GraphConnection[];
	parent: GraphNode;
	constructor(parent: GraphNode, name: string, connection_type: ConnectorType) {
		this.name = name;
		this.connection_type = connection_type;
		this.connections = [];
		this.parent = parent;
	}

	//Dont call this unless you are GraphEditor
	add_connection(connection: GraphConnection) {
		this.connections.push(connection);
	}

	render(center_x: number, center_y: number): SVGElement {
		let element = document.createElementNS("http://www.w3.org/2000/svg", "circle");
		element.setAttribute("cx", center_x.toString());
		element.setAttribute("cy", center_y.toString());
		element.setAttribute("r", "5");
		return element;
	}
}