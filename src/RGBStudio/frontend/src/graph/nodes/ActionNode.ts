import { defineNode, NodeInterface, NumberInterface, SelectInterface, setType, TextInputInterface } from "baklavajs";
import { actionEffectType, triggerActionType } from "./CustomNodeTypes";

export default defineNode({
    type: "Action",
    inputs: {
		input: () => new NodeInterface("Trigger", {}).use(setType, triggerActionType),
	},
	outputs: {
        output: () => new NodeInterface("Effect", {}).use(setType, actionEffectType),
    },
});