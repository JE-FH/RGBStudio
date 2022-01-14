import { ConnectorType } from "./ConnectorType";
import { GraphConnector } from "./GraphConnector";
import { GraphNode } from "./GraphNode";

export class GraphTargetConnector extends GraphConnector {
	constructor(parent: GraphNode, name: string, connection_type: ConnectorType) {
		super(parent, name, connection_type);
    }
}