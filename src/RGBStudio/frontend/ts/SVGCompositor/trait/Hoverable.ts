import {CSEvent} from "../CSEvent"

export type HoverEventHandler = (ev: MouseEvent) => void;
export type HoverEvent = CSEvent<HoverEventHandler>;
export interface Hoverable {
	readonly __RGBSTUDIO_SVGCOMPOSITOR_HOVERABLE_IMPLEMENTED: true;
	readonly Hovered: HoverEvent;
	readonly Unhovered: HoverEvent;
}

export function implements_hoverable(object: any): object is Hoverable {
	return typeof(object) == "object" &&
		object.__RGBSTUDIO_SVGCOMPOSITOR_HOVERABLE_IMPLEMENTED === true;
}