import { NodeInterfaceType } from "@baklavajs/interface-types";

export interface TriggerEvent {

}

export interface ActionEvent {
	isAttribute: boolean;
}

function hexToRgb(hex: string) {
	var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
	return result ? {
		r: parseInt(result[1], 16),
		g: parseInt(result[2], 16),
		b: parseInt(result[3], 16)
	} : null;
}

export class RGBColor {
	private _r: number;
	private _g: number;
	private _b: number;
	private constructor(r: number, g: number, b: number) {
		this._r = Math.min(Math.max(r, 0), 1);
		this._g = Math.min(Math.max(g, 0), 1);
		this._b = Math.min(Math.max(b, 0), 1);
	}

	static from_bytes(r: number, g: number, b: number) {
		return new RGBColor(r/255, g/255, b/255);
	}

	static from_hex(hexString: string) {
		let color = hexToRgb(hexString);
		if (color == null) {
			throw new Error("Invalid hex color")
		}
		return new RGBColor(color.r/255, color.g/255, color.b/255);
	}

	public get r(): number {
		return this._r;
	}

	public get g(): number {
		return this._g;
	}

	public get b(): number {
		return this._b;
    }

	get hex_color(): string {
		let r_hex = Math.round(this._r * 255).toString(16).padStart(2, "0");
		let g_hex = Math.round(this._g * 255).toString(16).padStart(2, "0");
		let b_hex = Math.round(this._b * 255).toString(16).padStart(2, "0");
		return `${r_hex}${g_hex}${b_hex}`;
	}

	set hex_color(value: string) {
		let color = hexToRgb(value);
		if (color == null) {
			throw new Error("Invalid hex color")
		}
		this._r = Math.min(Math.max(color.r / 255, 0), 1);
		this._g = Math.min(Math.max(color.g / 255, 0), 1);
		this._b = Math.min(Math.max(color.b / 255, 0), 1);
	}

	svg_color(): string {
		
		return `#${this.hex_color}`;
	}
}

export const actionEffectType = new NodeInterfaceType<ActionEvent>("actionEffectType");
export const triggerActionType = new NodeInterfaceType<TriggerEvent>("triggerActionType");
export const RGBColorType = new NodeInterfaceType<RGBColor>("RGBColorType");
export const KeyCodeType = new NodeInterfaceType<number>("KeyCodeType");
