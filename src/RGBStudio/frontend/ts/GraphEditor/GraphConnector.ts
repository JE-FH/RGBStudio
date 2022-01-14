import {ConnectorType} from "./ConnectorType";
import {GraphConnection} from "./GraphConnection";
import { GraphNode } from "./GraphNode";

export abstract class GraphConnector {
	name: string;
	connection_type: ConnectorType;
	connections: GraphConnection[];
	parent: GraphNode;
	relative_x: number;
	relative_y: number;
	constructor(parent: GraphNode, name: string, connection_type: ConnectorType) {
		this.name = name;
		this.connection_type = connection_type;
		this.connections = [];
		this.parent = parent;
		this.relative_x = 0;
		this.relative_y = 0;
	}

	//Dont call this unless you are GraphEditor
	add_connection(connection: GraphConnection) {
		this.connections.push(connection);
	}

	set_relative_position(x: number, y: number) {
		this.relative_x = x;
		this.relative_y = y;
    }

	get_absolute_center_pos(): [number, number] {
		return [
			this.parent.x + this.relative_x,
			this.parent.y + this.relative_y
		];
    }

	render(offset_x: number, offset_y: number): SVGElement {
		return this.connection_type.render_connector(offset_x + this.relative_x, offset_y + this.relative_y);
	}
}