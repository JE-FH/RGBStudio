import { SVGCompositor } from "../SVGCompositor";
import { Position, Widget } from "../Widget";


interface DragInstance {
	pointermove: (...args: any[]) => any;
	pointerup: (...args: any[]) => any;
	pointercancel: (...args: any[]) => any;
	pointer_id: number;
}

export class Dragifier {
	private widget: Widget;
	private drag_start_pos: Position;
	private widget_start_pos: Position;
	private capture_surface?: Element;
	private drag_instance?: DragInstance;

	constructor(widget: Widget) {
		this.widget = widget;
		this.drag_start_pos = {x: 0, y: 0};
		this.widget_start_pos = {x: 0, y: 0};
	}

	drag(ev: PointerEvent): void {
		//Only react on left click if a mouse triggers the event
		if (ev.pointerType == "mouse" && ev.button != 0) {
			return;
		}

		if (this.drag_instance != null) {
			this.stop_drag();
		}

		if (!(ev.target instanceof Element))  {
			return;
		}
		this.capture_surface = ev.target;

		this.drag_start_pos.x = ev.x;
		this.drag_start_pos.y = ev.y;

		this.widget_start_pos = this.widget.get_absolute_position();

		this.drag_instance = this.create_drag_instance(ev);
		this.capture_surface.setPointerCapture(ev.pointerId);
		this.capture_surface.addEventListener("pointermove", this.drag_instance.pointermove);
		this.capture_surface.addEventListener("pointerup", this.drag_instance.pointerup);
		this.capture_surface.addEventListener("pointercancel", this.drag_instance.pointercancel)
	}

	stop_drag(): void;
	stop_drag(ev: PointerEvent): void;
	stop_drag(ev?: PointerEvent) {
		if (this.drag_instance == null) {
			return;
		}

		if (this.capture_surface == null) {
			throw new Error("Dragifier error: drag_instance is not null but capture_surfaces has no elements");
		}

		if (ev?.pointerId != this.drag_instance.pointer_id) {
			return;
		}
		
		
		this.capture_surface.removeEventListener("pointermove", this.drag_instance.pointermove);
		this.capture_surface.removeEventListener("pointerup", this.drag_instance.pointerup);
		this.capture_surface.removeEventListener("pointercancel", this.drag_instance.pointercancel);
		this.capture_surface.releasePointerCapture(this.drag_instance.pointer_id);

		delete this.drag_instance;
	}

	private create_drag_instance(ev: PointerEvent): DragInstance {
		let instance: DragInstance = {
			pointer_id: ev.pointerId,
			pointermove: this.moved.bind(this),
			pointerup: () => {},
			pointercancel: () => {}
		};

		instance.pointerup = (ev) => {
			this.stop_drag(ev);
		};
		instance.pointercancel = (ev) => {
			this.stop_drag(ev);
		};
		return instance;
	}

	private moved(ev: PointerEvent) {
		if (this.drag_instance?.pointer_id != ev.pointerId) {
			return;
		}

		let offset_x = ev.x - this.drag_start_pos.x;
		let offset_y = ev.y - this.drag_start_pos.y;
		this.widget.move_to_absolute({
			x: this.widget_start_pos.x + offset_x,
			y: this.widget_start_pos.y + offset_y
		});
	}
}