import { Circle } from "../SVGCompositor/widgets/Circle";
import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { Json } from "../JSONRPC";
import { GraphNode } from "./GraphNode";
import { IGraphConnectorService } from "./GraphConnectorService";

export enum ConnectorDirection {
	Source,
	Target
}

export enum ConnectorType {
	Trigger,
	Action,
}


export class Connector extends GraphNodeAttribute {
	private _graphNode: GraphNode;
	private _type: ConnectorType;
	private _direction: ConnectorDirection;
	private _graphConnectorService: IGraphConnectorService;

	get Type(): ConnectorType {
		return this._type;
	}

	get Direction(): ConnectorDirection {
		return this._direction;
	}

	get GraphNode(): GraphNode {
		return this._graphNode;
    }

	public get_internal_representation(): Json {
		throw new Error("Method not implemented.");
	}

	constructor(name: string, graphNode: GraphNode, direction: ConnectorDirection, type: ConnectorType, graphConnectorService: IGraphConnectorService) {
		super(name);
		this._direction = direction;
		this._graphNode = graphNode;
		this._type = type;
		this._graphConnectorService = graphConnectorService;

		let circle_widget = CW(Circle, { radius: 5, relative_pos: { x: 0, y: 5 }, classes: ["trigger-connector"] });

		circle_widget.Clicked.add_listener(
			(ev) => this._graphConnectorService.clicked(this)
		);

		this.visual_container.add(circle_widget);
	}
}