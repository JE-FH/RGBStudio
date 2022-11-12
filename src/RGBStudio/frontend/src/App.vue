<script setup lang="ts">
import { provide } from 'vue';
import { RouterLink, RouterView } from 'vue-router'
import { RGBStudioAPISymbol } from './InjectionKeys';
import { FieldType, RGBStudioAPI } from './util/RGBStudioAPI';
import RGBStudioMockAPI from './util/RGBStudioMockAPI';

if (import.meta.env.DEV) {
	provide(RGBStudioAPISymbol, new RGBStudioMockAPI([
		{
			name: "test trigger",
			fields: {
				"Key code": {
					name: "Key code",
					type: FieldType.Integer,
				},
				"Trigger on release": {
					name: "Trigger on release",
					type: FieldType.Bool
				},
				"Trigger on press": {
					name: "Trigger on press",
					type: FieldType.Bool
				},
				"Trigger on repeat": {
					name: "Trigger on repeat",
					type: FieldType.Bool
				}
			}
		}
	], [
		{
			name: "Test effect",
			fields: {
				"Start fraction": {
					name: "Start fraction",
					type: FieldType.Number
				},
				"End fraction": {
					name: "End fraction",
					type: FieldType.Number
				},
				"Color": {
					name: "Color",
					type: FieldType.RGBColor
				}

			}
		}
	]));
} else {
	provide(RGBStudioAPISymbol, new RGBStudioAPI());
}
</script>

<template>
	<v-app>
		<v-app-bar title="RGBStudio"></v-app-bar>
		<v-main>
			<v-container no-gutters fluid class="primary fill-height pa-0">
				<RouterView />
			</v-container>
		</v-main>
	</v-app>
</template>

<style scoped>
</style>
