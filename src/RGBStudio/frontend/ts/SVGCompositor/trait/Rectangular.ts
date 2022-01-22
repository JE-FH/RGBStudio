import { Resizing } from "./Resizing";

interface BaseRectangular {
	readonly __RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: number;
	readonly width: number;
	readonly height: number;
}

export interface Rectangular extends BaseRectangular {
	readonly __RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: 1 | 2;
	
}

export interface ResizeableRectangular extends BaseRectangular, Resizing {
	readonly __RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED: 2;
	resize: (new_width: number, new_height: number) => void;
	readonly minimum_width: number;
	readonly minimum_height: number;
}

export function implements_rectangular(object: any): object is Rectangular {
	return typeof(object) == "object" &&
		typeof(object.__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED) == "number" &&
		object.__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED > 0;
}

export function implements_resizeable_rectangular(object: any): object is ResizeableRectangular {
	return typeof(object) == "object" &&
		typeof(object.__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED) == "number" &&
		object.__RGBSTUDIO_SVGCOMPOSITOR_RECTANGULAR_IMPLEMENTED === 2;
}