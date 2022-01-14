import { ConnectorType } from "./ConnectorType";

export class TriggerConnector extends ConnectorType {
    constructor() {
        super();
    }

    render_connector(center_x: number, center_y: number): SVGElement {
        let rv = document.createElementNS("http://www.w3.org/2000/svg", "circle");
        rv.setAttribute("cx", center_x.toString());
        rv.setAttribute("cy", center_y.toString());
        rv.setAttribute("r", "5");
        rv.setAttribute("fill", "#00FF00");
        return rv;
    }
}