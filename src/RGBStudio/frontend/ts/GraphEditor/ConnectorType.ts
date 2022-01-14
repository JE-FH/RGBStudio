export abstract class ConnectorType {
	constructor() {

	}

	abstract render_connector(center_x: number, center_y: number): SVGElement;
}