import { Rectangular, ResizeableRectangular } from "../trait/Rectangular";
import { Resizing } from "../trait/Resizing";
import { Widget } from "../Widget";

export interface AutoSizerOptions {
	padding: number;
	sync_width: boolean
	sync_height: boolean;
}

export class AutoSizer {
	private options: AutoSizerOptions;
	private container: Widget & Resizing & ResizeableRectangular;
	private content: Widget & Resizing;
	constructor(container: Widget & Resizing & ResizeableRectangular, content: Widget & Resizing, options: Partial<AutoSizerOptions>) {
		this.options = {
			padding: options.padding ?? 0,
			sync_width: options.sync_width ?? false,
			sync_height: options.sync_height ?? false
		}
		this.container = container;
		this.content = content;

		this.content.Resized.add_listener(this.on_resize.bind(this));

		this.on_resize();
	}

	on_resize() {
		let bb = this.content.calculate_bounding_box();
		bb.left = Math.max(bb.left, 0);
		bb.top = Math.max(bb.top, 0);
		bb.right = Math.max(bb.right, 0);
		bb.bottom = Math.max(bb.bottom, 0);

		let new_width = this.container.width;
		let new_height = this.container.height;

		if (this.options.sync_height)
			new_height = bb.bottom - bb.top + this.options.padding * 2;

		if (this.options.sync_width)
			new_width = bb.right - bb.left + this.options.padding * 2;

		this.container.resize(new_width, new_height);
	}
}