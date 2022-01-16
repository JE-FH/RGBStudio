import { Position, Widget } from "./Widget";


interface DragInstance {
	pointermove: (...args: any[]) => any;
	pointerleave: (...args: any[]) => any;
	pointerup: (...args: any[]) => any;
	pointer_id: number;
}

export class Dragifier {
	private widget: Widget;
	private drag_start_pos: Position;
	private widget_start_pos: Position;
	private _capture_zone: SVGElement;
	private drag_instances: Set<DragInstance>;

	public get capture_zone(): SVGElement {
		return this._capture_zone;
	}

	constructor(widget: Widget, capture_zone: SVGElement) {
		this.widget = widget;
		this.drag_start_pos = {x: 0, y: 0};
		this.widget_start_pos = {x: 0, y: 0};
		this._capture_zone = capture_zone;
		this.drag_instances = new Set();
	}

	drag(ev: PointerEvent): void {
		//Only react on left click if a mouse triggers the event
		if (ev.pointerType == "mouse" && ev.button != 0) {
			return;
		}
		
		console.log(ev);

		this.drag_start_pos.x = ev.x;
		this.drag_start_pos.y = ev.y;

		this.widget_start_pos = this.widget.get_absolute_position();

		let drag_instance = this.create_drag_instance(ev);

		this._capture_zone.setPointerCapture(ev.pointerId);
		this._capture_zone.addEventListener("pointermove", drag_instance.pointermove);
		this._capture_zone.addEventListener("pointerleave", drag_instance.pointerleave);
		this._capture_zone.addEventListener("pointerup", drag_instance.pointerup);
	}

	stop_all_drag() {
		this.drag_instances.forEach((drag_instance) => {
			this.stop_drag(drag_instance);
		})
	}

	private stop_drag(instance: DragInstance) {
		this._capture_zone.removeEventListener("pointermove", instance.pointermove);
		this._capture_zone.removeEventListener("pointerleave", instance.pointerleave);
		this._capture_zone.removeEventListener("pointerup", instance.pointerup);
		this._capture_zone.releasePointerCapture(instance.pointer_id);
	}

	private create_drag_instance(ev: PointerEvent): DragInstance {
		let instance: DragInstance = {
			pointer_id: ev.pointerId,
			pointermove: this.moved.bind(this),
			pointerleave: () => {},
			pointerup: () => {}
		};
		instance.pointerleave = this.stop_drag.bind(this, instance);
		instance.pointerup = instance.pointerleave;
		return instance;
	}

	private moved(ev: PointerEvent) {
		let offset_x = ev.x - this.drag_start_pos.x;
		let offset_y = ev.y - this.drag_start_pos.y;
		this.widget.move_to_absolute({
			x: this.widget_start_pos.x + offset_x,
			y: this.widget_start_pos.y + offset_y
		});
	}
}