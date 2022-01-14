import { GraphConnection } from "./GraphConnection";
import { GraphNode } from "./GraphNode";
import { GraphSourceConnector } from "./GraphSourceConnector";
import { GraphTargetConnector } from "./GraphTargetConnector";

export class GraphModel {
	nodes: GraphNode[];
	connections: GraphConnection[];
	constructor() {
		this.nodes = [];
		this.connections = [];
	}

	create_connection(source: GraphSourceConnector, target: GraphTargetConnector) {
		let connection = new GraphConnection(source, target);
		source.add_connection(connection);
		target.add_connection(connection);
		this.connections.push(new GraphConnection(source, target));
	}

	add_node(node: GraphNode) {
		this.nodes.push(node);
	}

	render(target: SVGElement) {
		for (let node of this.nodes) {
			node.render(target);
		}

		for (let connection of this.connections) {
			connection.render(target);
        }
    }
}