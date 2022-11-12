<script lang="ts" setup>
import "@baklavajs/themes/dist/classic.css";
import TestNode from "@/graph/nodes/TestNode";
import { EditorComponent, useBaklava } from "@baklavajs/renderer-vue";
import ActionNode from "@/graph/nodes/ActionNode";
import { inject } from "vue";
import { RGBStudioAPISymbol } from "@/InjectionKeys";
import { CreateEffectNode, CreateTriggerNode } from "@/graph/nodes/NodeGenerator";
import { BaklavaInterfaceTypes } from "baklavajs";
import { actionEffectType, triggerActionType } from "@/graph/nodes/CustomNodeTypes";
import CustomToolbar from "./CustomToolbar.vue";
import RGBLightRunnerCommands, { CreateLightningConfig } from "@/graph/RGBLightRunnerCommands";
import type { LightingConfig, TriggerInstanceConfig } from "@/util/RGBStudioAPI";
const baklava = useBaklava();
const api = inject(RGBStudioAPISymbol, () => {throw new Error("RGBStudioAPI was not provided");}, true);

const nodeInterfaceTypes = new BaklavaInterfaceTypes(baklava.editor, { viewPlugin: baklava });
nodeInterfaceTypes.addTypes(actionEffectType, triggerActionType);

baklava.editor.registerNodeType(ActionNode);
baklava.commandHandler.registerCommand(RGBLightRunnerCommands.APPLY_CONFIG, {
	canExecute: () => true,
	execute: async () => {
		await api.ApplyConfig(CreateLightningConfig(baklava.editor.graph));
	}
})



api.OnAddedTrigger.add_listener((addedTrigger) => {
	baklava.editor.registerNodeType(CreateTriggerNode(addedTrigger), {category: "Trigger"});
});

api.OnAddedEffect.add_listener((addedEffect) => {
	baklava.editor.registerNodeType(CreateEffectNode(addedEffect), {category: "Effect"});
});

api.Ready();


</script>

<template>
	<EditorComponent :view-model="baklava">
		<template v-slot:toolbar>
			<CustomToolbar :commandHandler="baklava.commandHandler" />
		</template>
	</EditorComponent>
</template>