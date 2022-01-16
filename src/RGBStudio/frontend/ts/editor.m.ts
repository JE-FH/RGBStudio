import { ActionNode } from "./GraphEditor/ActionNode";
import { GraphModel } from "./GraphEditor/GraphModel";
import { TriggerNode } from "./GraphEditor/TriggerNode";
import { Dragifier } from "./SVGCompositor/Dragifier";
import { Line } from "./SVGCompositor/Line";
import { Rectangle } from "./SVGCompositor/Rectangle";
import { RGBColor } from "./SVGCompositor/StyleHelper";
import { SVGCompositor } from "./SVGCompositor/SVGCompositor";

let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;

let svg_compositor = new SVGCompositor(svg_target);

let rect_container = new Rectangle({x: 10, y: 10}, {
	width: 100,
	height: 100,
	fill: RGBColor.from_bytes(255, 0, 0),
	rx: 10,
	ry: 10
})

let rect_container2 = new Rectangle({x: 150, y: 50}, {
	width: 50,
	height: 30,
	fill: RGBColor.from_bytes(255, 0, 0),
	rx: 10,
	ry: 10
})

let line = new Line({x: 0, y: 0}, {x: 0, y: 0}, {
	stroke: RGBColor.from_bytes(0, 0, 0)
});
rect_container.add(line.start);

let another_container = new Rectangle({x: 20, y: 30}, {
	width: 50,
	height: 10,
	fill: RGBColor.from_bytes(0, 255, 0)
});

rect_container2.add(line.end);

svg_compositor.add(rect_container);
rect_container.add(another_container);
svg_compositor.add(rect_container2);

svg_compositor.add_line(line);

(document as any).svg_compositor = rect_container;
(document as any).rect_container2 = rect_container2;

/*
let graph_model = new GraphModel();

let a = new TriggerNode("hello", 10, 10, 100, 100);

graph_model.add_node(a);

let b = new TriggerNode("hello2", 10, 150, 100, 100);

graph_model.add_node(b);

let c = new ActionNode("bing bong", 140, 30, 100, 100);

graph_model.add_node(c);


graph_model.create_connection(b.sources[0], c.targets[0]);
graph_model.create_connection(a.sources[0], c.targets[0]);

//We do get the SVGSVGElement even though we shouldnt but who cares
let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;

graph_model.render(svg_target);
*/
