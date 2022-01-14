import { GraphModel } from "./GraphEditor/GraphModel";
import { TriggerNode } from "./GraphEditor/TriggerNode";

let graph_model = new GraphModel();

graph_model.add_node(new TriggerNode("hello", 10, 10, 100, 100));

//We do get the SVGSVGElement even though we shouldnt but who cares
let svg_target = document.getElementById("target")! as unknown as SVGSVGElement;

graph_model.render(svg_target);
