import {CSEvent} from "../CSEvent"

export type ClickEventHandler = (ev: PointerEvent) => void;
export type ClickEvent = CSEvent<ClickEventHandler>;
export interface Clickable {
	readonly __RGBSTUDIO_SVGCOMPOSITOR_CLICKABLE_IMPLEMENTED: true;
	readonly Clicked: ClickEvent;
}

export function implements_clickable(object: any): object is Clickable {
	return typeof(object) == "object" &&
		object.__RGBSTUDIO_SVGCOMPOSITOR_CLICKABLE_IMPLEMENTED === true;
}