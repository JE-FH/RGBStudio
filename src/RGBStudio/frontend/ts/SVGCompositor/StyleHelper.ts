export class RGBColor {
	private r: number;
	private g: number;
	private b: number;
	private constructor(r: number, g: number, b: number) {
		this.r = Math.min(Math.max(r, 0), 1);
		this.g = Math.min(Math.max(g, 0), 1);
		this.b = Math.min(Math.max(b, 0), 1);
	}

	static from_bytes(r: number, g: number, b: number) {
		return new RGBColor(r/255, g/255, b/255);
	}

	svg_color(): string {
		let r_hex = Math.round(this.r * 255).toString(16).padStart(2, "0");
		let g_hex = Math.round(this.g * 255).toString(16).padStart(2, "0");
		let b_hex = Math.round(this.b * 255).toString(16).padStart(2, "0");
		return `#${r_hex}${g_hex}${b_hex}`;
	}
}