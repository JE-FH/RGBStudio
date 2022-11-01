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
	required: boolean;
	type: string;
}

export interface TriggerType {
	name: string;
	fields: { [key: string]: TriggerField };
}

export class TriggerNode extends GraphNode {
	private sourceAttribute: Connector;
	private _graphConnectorService: IGraphConnectorService;

	constructor(container: WidgetContainer, name: string, dragable: boolean, readOnly: boolean, graphConnectorService: IGraphConnectorService) {
		super(container, "trigger", name, dragable);
		this._graphConnectorService = graphConnectorService;
		this.sourceAttribute = new Connector("trigger", this, ConnectorDirection.Source, ConnectorType.Trigger, graphConnectorService);
		this._graphConnectorService.addConnector(this.sourceAttribute);
		this.add_attribute(this.sourceAttribute);
	}

	addLineEndToSource(lineEnd: LineEnd) {
		this.sourceAttribute.visual_container.add(lineEnd);
    }

	static from_trigger_type(container: WidgetContainer, name: string, trigger_type: TriggerType, dragable: boolean, readOnly: boolean, graphConnectorService: IGraphConnectorService): TriggerNode {
		let rv = new TriggerNode(container, name, dragable, readOnly, graphConnectorService);

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
