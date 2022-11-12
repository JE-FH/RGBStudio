import type { DynamicConfigAttribute, EffectInstanceConfig, LightingConfig, TriggerInstanceConfig } from "@/util/RGBStudioAPI";
import { CheckboxInterface, IntegerInterface, NodeInterface, NumberInterface, TextInputInterface, type AbstractNode, type Graph } from "baklavajs";
import { ColorPickerInterface } from "@/graph/Interfaces/ColorPickerInterface";

const RGBLightRunnerCommands = {
	APPLY_CONFIG: "RGBLightRunnerCommands.APPLY_CONFIG"
};

function GetTypeAndName(node: AbstractNode): {type: "trigger" | "effect", id: string} | {type: "action"}{
	if (node.type == "Action") {
		return {type: "action"};
	}

	let match = node.type.match(/^(trigger|effect)#(.*)$/);
	if (match == null) {
		throw new Error("Invalid node type found called " + node.type);
	}

	return {type: match[1] as ("trigger" | "effect"), id: match[2]};
}

function GetInstanceName(node: AbstractNode) {
	let info = GetTypeAndName(node);
	if (info.type == "action") {
		return `action##${node.id}#${node.title}`;
	}
	return `${info.type}#${info.id}#${node.id}#${node.title}`;
}

function FormatNodeConnection(node: AbstractNode, nodeInterface: NodeInterface) {
	return `${GetInstanceName(node)}.${nodeInterface.name}`;
}

function EncodeInterfaceValue(nodeInterface: NodeInterface<any>): string {
	if (nodeInterface instanceof TextInputInterface) {
		return nodeInterface.value;
	} else if (nodeInterface instanceof NumberInterface) {
		return nodeInterface.value.toString();
	} else if (nodeInterface instanceof IntegerInterface) {
		return nodeInterface.value.toString();
	} else if (nodeInterface instanceof CheckboxInterface) {
		return nodeInterface.value ? "true" : "false";
	} else if (nodeInterface instanceof ColorPickerInterface) {
		return nodeInterface.value.hex_color;
	} else if (nodeInterface instanceof NodeInterface) {
		return "";
	} 
	console.log(nodeInterface);
	throw new Error("Unsupported interface type");
}

function CreateAttributes(inputs: Record<string, NodeInterface<any>>): DynamicConfigAttribute[] {
	return Object.keys(inputs)
		.map((inputKey) => inputs[inputKey])
		.map((input) => {
			console.log(input)
			return {name: input.name, value: EncodeInterfaceValue(input)};
		})
}


export function CreateLightningConfig(graph: Graph): LightingConfig {
	let config: LightingConfig = {
		triggerInstances: [],
		triggerActionEdges: [],
		actionEffectEdges: [],
		effectInstances: []
	}
	for (let node of graph.nodes) {
		let info = GetTypeAndName(node);
		
		if (info.type == "trigger") {
			let triggerInstance: TriggerInstanceConfig = {
				instanceId: GetInstanceName(node),
				triggerId: info.id,
				attributes: CreateAttributes(node.inputs)
			};

			config.triggerInstances.push(triggerInstance);
		 } else if (info.type == "effect") {
			let effectInstance: EffectInstanceConfig = {
				instanceId: GetInstanceName(node),
				effectId: info.id,
				attributes: CreateAttributes(node.inputs)
			};

			config.effectInstances.push(effectInstance);
		}
	}
	for (let connection of graph.connections) {
		let fromNode = graph.findNodeById(connection.from.nodeId)!;
		let toNode = graph.findNodeById(connection.to.nodeId)!;

		let fromNodeInfo = GetTypeAndName(fromNode);
		if (fromNodeInfo.type == "action") {
			config.actionEffectEdges.push({
				actionName: GetInstanceName(fromNode),
				effectInstanceId: GetInstanceName(toNode)
			});
		} else {
			config.triggerActionEdges.push({
				triggerInstanceId: GetInstanceName(fromNode),
				actionName: GetInstanceName(toNode)
			});
		}

		console.log(`${FormatNodeConnection(fromNode, connection.from)} -> ${FormatNodeConnection(toNode, connection.to)}`)
	}

	return config;
}

export default RGBLightRunnerCommands;