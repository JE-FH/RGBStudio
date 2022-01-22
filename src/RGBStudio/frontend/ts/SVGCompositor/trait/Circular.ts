export interface Circular {
	readonly __RGBSTUDIO_SVGCOMPOSITOR_CIRCULAR_IMPLEMENTED: true;
	readonly radius: number;
	resize: (new_radius: number) => void;
}

export function implements_circular(object: any): object is Circular {
	return typeof(object) == "object" &&
		object.__RGBSTUDIO_SVGCOMPOSITOR_CIRCULAR_IMPLEMENTED === true;
}