import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { LineEnd } from "../SVGCompositor/widgets/LineEnd";
import { Connector, ConnectorDirection, ConnectorType } from "./Connector";
import { IGraphConnectorService } from "./GraphConnectorService";
import { GraphNode } from "./GraphNode";

export class ActionNode extends GraphNode {
	private _source: Connector;
	private _target: Connector;

	constructor(container: WidgetContainer, name: string, dragable: boolean, graphConnectorService: IGraphConnectorService) {
		super(container, "action", name, dragable);
		this._source = new Connector("source", this, ConnectorDirection.Source, ConnectorType.Action, graphConnectorService);
		this._target = new Connector("target", this, ConnectorDirection.Target, ConnectorType.Trigger, graphConnectorService);
		this.add_attribute(this._source);
		this.add_attribute(this._target);
		graphConnectorService.addConnector(this._source);
		graphConnectorService.addConnector(this._target);
	}

	addLineEndToTarget(lineEnd: LineEnd) {
		this._target.visual_container.add(lineEnd);
	}
}
