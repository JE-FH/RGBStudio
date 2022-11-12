<script lang="ts" setup>
import type { ICommandHandler } from 'baklavajs';


const props = defineProps<{
	commandHandler: ICommandHandler,
	command: string,
	title: string
}>();

</script>

<template>
	<button
        class="baklava-toolbar-entry baklava-toolbar-button"
        :disabled="!commandHandler.canExecuteCommand(command)"
        :title="title"
        @click="commandHandler.executeCommand(command)"
    >
        {{ title }}
    </button>
</template>