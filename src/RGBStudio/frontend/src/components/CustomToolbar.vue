<script lang="ts" setup>
import RGBLightRunnerCommands from "@/graph/RGBLightRunnerCommands";
import { Commands } from "@baklavajs/renderer-vue";
import type { ICommandHandler } from 'baklavajs';
import CustomToolbarButton from './CustomToolbarButton.vue';

const commands = [
	{ command: Commands.COPY_COMMAND, title: "Copy" },
	{ command: Commands.PASTE_COMMAND, title: "Paste" },
	{ command: Commands.UNDO_COMMAND, title: "Undo" },
	{ command: Commands.REDO_COMMAND, title: "Redo" },
	{ command: RGBLightRunnerCommands.APPLY_CONFIG, title: "Apply config" }
];

const props = defineProps<{
	commandHandler: ICommandHandler
}>();

</script>

<template>
	<div class="baklava-toolbar">
		<CustomToolbarButton 
			v-for="command in commands" 
			:key="command.command"
			:command-handler="props.commandHandler"
			:command="command.command"
			:title="command.title"
		/>
	</div>
</template>