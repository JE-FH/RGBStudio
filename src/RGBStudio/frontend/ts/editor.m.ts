import { GraphModel } from "./GraphEditor/GraphModel";
import { TriggerNode } from "./GraphEditor/TriggerNode";

let graph_model = new GraphModel();

let a = new TriggerNode("hello", 10, 10, 100, 100);

graph_model.add_node(a);

let b = new TriggerNode("hello2", 10, 150, 100, 100);

graph_model.add_node(b);

//We do get the SVGSVGElement even though we shouldnt but who cares
let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;

graph_model.render(svg_target);
