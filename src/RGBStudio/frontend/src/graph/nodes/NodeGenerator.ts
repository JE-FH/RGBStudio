import { FieldType, type EffectDescription, type TriggerDescription } from "@/util/RGBStudioAPI";
import { CheckboxInterface, defineNode, IntegerInterface, NodeInterface, NumberInterface, setType, TextInputInterface, type InterfaceFactory } from "baklavajs";
import { ColorPickerInterface } from "../Interfaces/ColorPickerInterface";
import { KeyCodePickerInterface } from "../Interfaces/KeyCodePickerInterface";
import { actionEffectType, triggerActionType } from "./CustomNodeTypes";

function FieldTypeToNode(name: string, fieldType: FieldType) {
	switch (fieldType) {
		case FieldType.String:
			return () => new TextInputInterface(name, "").setPort(false);
		case FieldType.Number:
			return () => new NumberInterface(name, 0).setPort(false);
		case FieldType.Integer:
			return () => new IntegerInterface(name, 0).setPort(false);
		case FieldType.Bool:
			return () => new CheckboxInterface(name, false).setPort(false);
		case FieldType.Action:
			return () => new NodeInterface(name, {isAttribute: true}).use(setType, actionEffectType);
		case FieldType.RGBColor:
			return () => new ColorPickerInterface(name).setPort(false);
		case FieldType.KeyCode:
			return () => new KeyCodePickerInterface(name).setPort(false);
		default:
			throw new Error("Unsupported field type: " + fieldType);
	}
}

export function CreateTriggerNode(triggerDescription: TriggerDescription) {
	let inputs: InterfaceFactory<any>  = {};
	for (let [key, field] of Object.entries(triggerDescription.fields)) {
		if (field.type == FieldType.Action) {
			throw new Error("Action properties are unsupported in triggers");
		}
		inputs[field.name] = FieldTypeToNode(field.name, field.type);
		
	}

	let outputs: InterfaceFactory<any> = {};
	for (let subTrigger of triggerDescription.subTriggers) {
		outputs[subTrigger] = () => new NodeInterface(subTrigger, {}).use(setType, triggerActionType)
	}

	return defineNode({
		title: triggerDescription.name,
		type: `trigger#${triggerDescription.name}`,
		inputs: inputs,
		outputs: outputs,
	});
}

export function CreateEffectNode(effectDescription: EffectDescription) {
	let inputs: InterfaceFactory<any>  = {};
	for (let fieldKey of Object.keys(effectDescription.fields)) {
		let field = effectDescription.fields[fieldKey];
		inputs[field.name] = FieldTypeToNode(field.name, field.type);
	}
	return defineNode({
		title: effectDescription.name,
		type: `effect#${effectDescription.name}`,
		inputs: {
			...inputs,
			action: () => new NodeInterface("Action", {isAttribute: false}).use(setType, actionEffectType)
		},
	});
}
