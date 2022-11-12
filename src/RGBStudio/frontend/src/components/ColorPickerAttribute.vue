<script lang="ts" setup>
import type { ColorPickerInterface } from '@/graph/Interfaces/ColorPickerInterface';
import { RGBColor } from '@/graph/nodes/CustomNodeTypes';
import { computed, ref } from 'vue';

const props = defineProps<{
	intf: ColorPickerInterface
}>()

const colorModel = computed<string>({
	get() {
		return props.intf.value.hex_color;
	},
	set(val: string) {
		props.intf.value.hex_color = val;
	}
});

const dialog = ref(false);

</script>

<template>
	<div>
		<div>{{props.intf.name}}</div>
		<v-btn
			:color="props.intf.value.svg_color()"
			dark
			@click="dialog = true"
			style="width:100%"
		/>
		<v-dialog
    	  v-model="dialog"
    	  width="500"
    	>
			<v-card>
				<v-card-text>
					<v-color-picker v-model="colorModel" mode="rgb" flat />
					<v-btn @click="dialog = false">OK</v-btn>
				</v-card-text>
			</v-card>
		</v-dialog>
	</div>
</template>