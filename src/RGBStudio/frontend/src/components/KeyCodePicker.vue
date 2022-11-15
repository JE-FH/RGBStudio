<script lang="ts" setup>
import { ref } from 'vue';
import VKTranslationsCsv from '@/assets/VKTranslations.Nordic.csv?raw'
import CsvReader from '@/util/CsvReader';
import { computed, defineProps } from 'vue';

let parsed = new CsvReader().ReadCsvAndTransform(VKTranslationsCsv, {
	VKCode: (val) => Number(val ?? -1),
	JsName: (val) => val ?? undefined
});

let VKLookupTable = new Map(Object.values(parsed).map(x => [x.JsName, x.VKCode]));
let JSNameLookupTable = new Map(Object.values(parsed).map(x => [x.VKCode, x.JsName]));

const props =  defineProps<{
	modelValue: number,
	label: string
}>();

const emits = defineEmits<{
	(e: "update:modelValue", value: number): void
}>();

const selectedKeyJsName = computed(() => JSNameLookupTable.get(props.modelValue) ?? "Unknown")

const displayedValue = computed(() => {
	if (props.modelValue == -1) {
		return "Any key";
	} else {
		return `${selectedKeyJsName.value} (${props.modelValue})`;
	}
});


function keyDown(ev: KeyboardEvent) {
	emits("update:modelValue", VKLookupTable.get(ev.code) ?? -1);
}

function beforeInput(ev: Event) {
	ev.preventDefault();
}

function onClear() {
	emits("update:modelValue", -1);
}

</script>

<template>
	<v-text-field @click:clear="onClear" density="compact" clearable :label="props.label" type="text" :model-value="displayedValue" @keydown="keyDown" @beforeinput="beforeInput"/>
</template>