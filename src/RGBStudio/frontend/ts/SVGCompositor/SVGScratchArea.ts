export abstract class SVGScratchArea {
	private static _scratch_area: SVGElement;
	static get scratch_area(): SVGElement {
		if (this._scratch_area == null) {
			throw new Error("SVGScratchAreas has not been set up");
		}
		return SVGScratchArea._scratch_area;
	}

	static setup(scratch_area: SVGElement) {
		this._scratch_area = scratch_area;
	}
}