<script setup lang="ts">
import { provide } from 'vue';
import { RouterLink, RouterView } from 'vue-router'
import { RGBStudioAPISymbol } from './InjectionKeys';
import { FieldType, RGBStudioAPI } from './util/RGBStudioAPI';
import RGBStudioMockAPI from './util/RGBStudioMockAPI';

if (import.meta.env.DEV) {
	console.log("Dev mode, using mock API");
	provide(RGBStudioAPISymbol, new RGBStudioMockAPI([
		{
			name: "test trigger",
			fields: {
				"Key code": {
					name: "Key code",
					type: FieldType.KeyCode,
				}
			},
			subTriggers: [
				"released",
				"pressed",
				"repeated"
			]
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
				},
				"Stop": {
					name: "Stop",
					type: FieldType.Action
				}

			}
		}
	]));
} else {
	console.log("Production mode, using real API");
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
