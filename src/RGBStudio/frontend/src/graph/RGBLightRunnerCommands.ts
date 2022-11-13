import type { DynamicConfigAttribute, EffectInstanceConfig, LightingConfig, TriggerInstanceConfig } from "@/util/RGBStudioAPI";
import { CheckboxInterface, Connection, IntegerInterface, NodeInterface, NumberInterface, TextInputInterface, type AbstractNode, type Graph } from "baklavajs";
import { ColorPickerInterface } from "@/graph/Interfaces/ColorPickerInterface";
import { KeyCodePickerInterface } from "./Interfaces/KeyCodePickerInterface";

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
		return `${node.id}#${node.title}`;
	}
	return `${node.id}#${node.title}`;
}

function FormatNodeConnection(node: AbstractNode, nodeInterface: NodeInterface) {
	return `${GetInstanceName(node)}.${nodeInterface.name}`;
}

function EncodeInterfaceValue(nodeInterface: NodeInterface<any>, graph: Graph): string {
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
	} else if (nodeInterface instanceof KeyCodePickerInterface) {
		return nodeInterface.value.toString();
	} else if (nodeInterface instanceof NodeInterface) {
		if (nodeInterface.value?.isAttribute == true) {
			let connection = graph.connections.find((connection) => connection.to.id == nodeInterface.id);
			if (connection == null) {
				return "";
			}
			let node = graph.findNodeById(connection.from.nodeId);
			if (node == null) {
				throw new Error("Could not find node by id");
			}
			return GetInstanceName(node);
		}
		return "";
	} 
	console.log(nodeInterface);
	throw new Error("Unsupported interface type");
}

function CreateAttributes(inputs: Record<string, NodeInterface<any>>, graph: Graph): DynamicConfigAttribute[] {
	return Object.keys(inputs)
		.map((inputKey) => inputs[inputKey])
		.map((input) => {
			return {name: input.name, value: EncodeInterfaceValue(input, graph)};
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
				attributes: CreateAttributes(node.inputs, graph)
			};

			config.triggerInstances.push(triggerInstance);
		 } else if (info.type == "effect") {
			let effectInstance: EffectInstanceConfig = {
				instanceId: GetInstanceName(node),
				effectId: info.id,
				attributes: CreateAttributes(node.inputs, graph)
			};

			config.effectInstances.push(effectInstance);
		}
	}
	for (let connection of graph.connections) {
		let fromNode = graph.findNodeById(connection.from.nodeId)!;
		let toNode = graph.findNodeById(connection.to.nodeId)!;

		let fromNodeInfo = GetTypeAndName(fromNode);
		if (fromNodeInfo.type == "action") {
			if (connection.to.value?.isAttribute == true) {
			} else {
				config.actionEffectEdges.push({
					actionName: GetInstanceName(fromNode),
					effectInstanceId: GetInstanceName(toNode)
				});
			}
		} else {
			config.triggerActionEdges.push({
				triggerInstanceId: GetInstanceName(fromNode) + "." + connection.from.name,
				actionName: GetInstanceName(toNode)
			});
		}
	}

	return config;
}

export default RGBLightRunnerCommands;