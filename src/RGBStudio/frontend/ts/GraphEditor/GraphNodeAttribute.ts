import { Json } from "../JSONRPC";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { WidgetContainer } from "../SVGCompositor/WidgetContainer";
import { FlexBox } from "../SVGCompositor/widgets/FlexBox";
import { TextWidget } from "../SVGCompositor/widgets/TextWidget";

export abstract class GraphNodeAttribute {
	private _visual_container: FlexBox;
	public get visual_container(): FlexBox {
		return this._visual_container;
	}
	protected set visual_container(value: FlexBox) {
		this._visual_container = value;
	}
	
	private name_text_node: TextWidget;

	private _name: string = "";
	public get Name(): string {
		return this._name;
	}
	private set Name(value: string) {
		this._name = value;
		
	}
	
	constructor(name: string) {
		this._name = name;
		this.name_text_node = CW(TextWidget, {text: name, classes: ["attribute-text"]});
		this._visual_container = CW(FlexBox, {min_distance: 10},
			this.name_text_node
		);
	}

	public abstract get_internal_representation(): string;

}