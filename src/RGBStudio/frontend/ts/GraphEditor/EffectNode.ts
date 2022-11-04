import { RGBColor } from "../SVGCompositor/StyleHelper";
import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { LineEnd } from "../SVGCompositor/widgets/LineEnd";
import { BoolAttribute } from "./BoolAttribute";
import { ColorAttribute } from "./ColorAttribute";
import { Connector, ConnectorDirection, ConnectorType } from "./Connector";
import { IGraphConnectorService } from "./GraphConnectorService";
import { GraphNode } from "./GraphNode";
import { NumberAttribute } from "./NumberAttribute";

interface EffectField {
	name: string;
	type: string;
}

export interface EffectType {
	name: string;
	fields: { [key: string]: EffectField };
}

export class EffectNode extends GraphNode {
	private _targetAttribute: Connector;
	private _graphConnectorService: IGraphConnectorService;
	private _effectType: EffectType;
	private _id: string;

	public get EffectType(): EffectType {
		return this._effectType;
	}

	public get UID(): string {
		return `${this._effectType.name}#${this._id}`;
	}

	constructor(container: WidgetContainer, effectType: EffectType, id: string, dragable: boolean, readOnly: boolean, graphConnectorService: IGraphConnectorService) {
		super(container, "action", effectType.name, dragable);
		this._graphConnectorService = graphConnectorService;
		this._effectType = effectType;
		this._id = id;
		this._targetAttribute = new Connector("action", this, ConnectorDirection.Target, ConnectorType.Action, graphConnectorService, readOnly, false);
		this._graphConnectorService.addConnector(this._targetAttribute);
		this.add_attribute(this._targetAttribute);

	}

	AddLineEndToTarget(lineEnd: LineEnd) {
		this._targetAttribute.AddLineEnd(lineEnd);
	}

	static from_effect_type(container: WidgetContainer, id: string, effect_type: EffectType, dragable: boolean, readOnly: boolean, graphConnectorService: IGraphConnectorService): EffectNode {
		let rv = new EffectNode(container, effect_type, id, dragable, readOnly, graphConnectorService);

		for (let [field_name, field] of Object.entries(effect_type.fields)) {
			if (field.type == "Integer") {
				rv.add_attribute(new NumberAttribute(field.name, 1, readOnly));
			} else if (field.type == "Number") {
				rv.add_attribute(new NumberAttribute(field.name, 1, readOnly));
			} else if (field.type == "RGBColor") {
				rv.add_attribute(new ColorAttribute(field.name, RGBColor.from_bytes(255, 255, 255), readOnly));
			} else if (field.type == "Bool") {
				rv.add_attribute(new BoolAttribute(field.name, false, readOnly));
			} else if (field.type == "Action") {
				let connector = new Connector(field.name, rv, ConnectorDirection.Target, ConnectorType.Action, graphConnectorService, readOnly, true);
				graphConnectorService.addConnector(connector);
				rv.add_attribute(connector);
            } else {
				console.log(`Unknown attribute type for ${field_name}`, field);
			}
		}
		return rv;
	}
}
