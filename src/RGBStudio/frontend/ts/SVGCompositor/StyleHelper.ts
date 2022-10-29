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

	public get r(): number {
		return this._r;
	}

	public get g(): number {
		return this._g;
	}

	public get b(): number {
		return this._b;
    }

	svg_color(): string {
		let r_hex = Math.round(this._r * 255).toString(16).padStart(2, "0");
		let g_hex = Math.round(this._g * 255).toString(16).padStart(2, "0");
		let b_hex = Math.round(this._b * 255).toString(16).padStart(2, "0");
		return `#${r_hex}${g_hex}${b_hex}`;
	}
}