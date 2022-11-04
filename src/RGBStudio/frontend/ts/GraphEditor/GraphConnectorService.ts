import { ActionNode } from "./ActionNode";
import { Connector, ConnectorDirection, ConnectorType } from "./Connector";
import { IGraphEditorService } from "./GraphEditor";
import { TriggerNode } from "./TriggerNode";
import { EffectNode } from "./EffectNode";

export interface IGraphConnectorService {
    addConnector(source: Connector): void;
    clicked(connector: Connector): void;
}

interface AnyEdge {
	source: Connector,
	target: Connector
}

export class GraphConnectorService implements IGraphConnectorService {
    private _connectors: Connector[];
	private _startConnector: Connector | null;
	private _graphEditorService: IGraphEditorService;

	constructor(graphEditorService: IGraphEditorService) {
		this._connectors = [];
		this._graphEditorService = graphEditorService;
        this._startConnector = null;
	}

	addConnector(connector: Connector): void {
		this._connectors.push(connector);
	}

	clicked(connector: Connector): void {
		if (this._startConnector == null) {
			this._startConnector = connector;
		} else {
			if (this._startConnector.Direction == connector.Direction)
				return;
			if (this._startConnector.Type != connector.Type)
				return;

			let edge = this.getEdge(this._startConnector, connector);
			if (edge.source.Type == ConnectorType.Trigger) {
				if (edge.source.GraphNode instanceof TriggerNode && edge.target.GraphNode instanceof ActionNode) {
					this._graphEditorService.AddTriggerActionEdge(edge.source.GraphNode, edge.target.GraphNode);
					this._startConnector = null;
				}
			} else if (edge.source.Type == ConnectorType.Action) {
				if (edge.source.GraphNode instanceof ActionNode && edge.target.GraphNode instanceof EffectNode) {
					if (edge.target.IsCustom) {
						this._graphEditorService.AddActionAttributeEdge(edge.source.GraphNode, edge.target.GraphNode, edge.target);
					} else {
						this._graphEditorService.AddActionEffectEdge(edge.source.GraphNode as ActionNode, edge.target.GraphNode as EffectNode);
						this._startConnector = null;
					}
				}
            }
		}
	}

	private getEdge(a: Connector, b: Connector): AnyEdge {
		if (a.Direction == ConnectorDirection.Source && b.Direction == ConnectorDirection.Target)
			return { source: a, target: b };
		if (b.Direction == ConnectorDirection.Source && a.Direction == ConnectorDirection.Target)
			return { source: b, target: a };
		throw new Error("a and b needs to be different direction");
	}
}
