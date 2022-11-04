import { Circle } from "../SVGCompositor/widgets/Circle";
import { GraphNodeAttribute } from "./GraphNodeAttribute";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { Json } from "../JSONRPC";
import { GraphNode } from "./GraphNode";
import { IGraphConnectorService } from "./GraphConnectorService";
import { LineEnd } from "../SVGCompositor/widgets/LineEnd";

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
	private _circleWidget: Circle;
	private _isCustom: boolean;

	get Type(): ConnectorType {
		return this._type;
	}

	get Direction(): ConnectorDirection {
		return this._direction;
	}

	get GraphNode(): GraphNode {
		return this._graphNode;
	}

	get IsCustom() {
		return this._isCustom;
    }

	public get_internal_representation(): Json {
		return "";
	}

	public AddLineEnd(lineEnd: LineEnd) {
		this._circleWidget.add(lineEnd);
	}

	constructor(name: string, graphNode: GraphNode, direction: ConnectorDirection, type: ConnectorType, graphConnectorService: IGraphConnectorService, readOnly: boolean, isCustom: boolean) {
		super(name);
		this._direction = direction;
		this._graphNode = graphNode;
		this._type = type;
		this._graphConnectorService = graphConnectorService;
		this._isCustom = isCustom;

		this._circleWidget = CW(Circle, { radius: 5, relative_pos: { x: 0, y: 5 }, classes: ["trigger-connector"] });

		if (!readOnly) {
			this._circleWidget.Clicked.add_listener(
				(ev) => this._graphConnectorService.clicked(this)
			);
		}

		this.visual_container.add(this._circleWidget);
	}
}