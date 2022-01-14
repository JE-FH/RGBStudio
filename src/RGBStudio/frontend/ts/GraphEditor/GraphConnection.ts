import { GraphSourceConnector } from "./GraphSourceConnector";
import { GraphTargetConnector } from "./GraphTargetConnector";

export class GraphConnection {
	source: GraphSourceConnector;
	target: GraphTargetConnector;
	constructor(source: GraphSourceConnector, target: GraphTargetConnector) {
		this.source = source;
		this.target = target;
	}
}