<script lang="ts" setup>
import type { KeyCodePickerInterface } from '@/graph/Interfaces/KeyCodePickerInterface';
import KeyCodePicker from './KeyCodePicker.vue';

const props = defineProps<{
	intf: KeyCodePickerInterface
}>()



</script>

<template>
	<div>
		<KeyCodePicker :label="props.intf.name" v-model="props.intf.value" />
	</div>
</template>