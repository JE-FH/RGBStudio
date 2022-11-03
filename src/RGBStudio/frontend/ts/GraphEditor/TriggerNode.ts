import { RGBColor } from "../SVGCompositor/StyleHelper";
import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { LineEnd } from "../SVGCompositor/widgets/LineEnd";
import { BoolAttribute } from "./BoolAttribute";
import { ColorAttribute } from "./ColorAttribute";
import { Connector, ConnectorDirection, ConnectorType } from "./Connector";
import { IGraphConnectorService } from "./GraphConnectorService";
import { IGraphEditorService } from "./GraphEditor";
import { GraphNode } from "./GraphNode";
import { NumberAttribute } from "./NumberAttribute";

interface TriggerField {
	name: string;
	type: string;
}

export interface TriggerType {
	name: string;
	fields: { [key: string]: TriggerField };
}

export class TriggerNode extends GraphNode {
	private sourceAttribute: Connector;
	private _graphConnectorService: IGraphConnectorService;
	private _triggerType: TriggerType;
	private _id: string;

	public get TriggerType(): TriggerType {
		return this._triggerType;
	}

	public get UID(): string {
		return `${this._triggerType.name}#${this._id}`;
    }

	constructor(container: WidgetContainer, triggerType: TriggerType, id: string, dragable: boolean, readOnly: boolean, graphConnectorService: IGraphConnectorService) {
		super(container, "trigger", triggerType.name, dragable);
		this._graphConnectorService = graphConnectorService;
		this._triggerType = triggerType;
		this._id = id;
		this.sourceAttribute = new Connector("trigger", this, ConnectorDirection.Source, ConnectorType.Trigger, graphConnectorService);
		this._graphConnectorService.addConnector(this.sourceAttribute);
		this.add_attribute(this.sourceAttribute);

	}

	addLineEndToSource(lineEnd: LineEnd) {
		this.sourceAttribute.visual_container.add(lineEnd);
	}

	static from_trigger_type(container: WidgetContainer, id: string, trigger_type: TriggerType, dragable: boolean, readOnly: boolean, graphConnectorService: IGraphConnectorService): TriggerNode {
		let rv = new TriggerNode(container, trigger_type, id, dragable, readOnly, graphConnectorService);

		for (let [field_name, field] of Object.entries(trigger_type.fields)) {
			if (field.type == "Integer") {
				rv.add_attribute(new NumberAttribute(field.name, 1, readOnly));
			} else if (field.type == "Number") {
				rv.add_attribute(new NumberAttribute(field.name, 1, readOnly));
			} else if (field.type == "RGBColor") {
				rv.add_attribute(new ColorAttribute(field.name, RGBColor.from_bytes(255, 255, 255), readOnly));
			} else if (field.type == "Bool") {
				rv.add_attribute(new BoolAttribute(field.name, false, readOnly));
			} else {
				console.log(`Unknown attribute type for ${field_name}`, field);
			}
		}
		return rv;
    }
}
