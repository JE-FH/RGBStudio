import { CSEvent } from "../CSEvent";

export type ResizeEventHandler = () => void;
export type ResizeEvent = CSEvent<ResizeEventHandler>;

export interface Resizing {
	readonly __RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED: true;
	readonly Resized: ResizeEvent;
}

export function implements_resizing(object: any): object is Resizing {
	return typeof(object) == "object" &&
		object.__RGBSTUDIO_SVGCOMPOSITOR_RESIZING_IMPLEMENTED === true;
}