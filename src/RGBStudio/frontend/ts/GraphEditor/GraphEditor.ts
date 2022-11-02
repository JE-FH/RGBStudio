import { Dragifier } from "../SVGCompositor/behavior/Dragifier";
import { SVGCompositor } from "../SVGCompositor/SVGCompositor";
import { ToolWindow } from "../SVGCompositor/ToolWindow";
import { CreateWidget2 as CW } from "../SVGCompositor/WidgetConstructor";
import { FlexBox } from "../SVGCompositor/widgets/FlexBox";
import { PaddedContainer, padding } from "../SVGCompositor/widgets/PaddedContainer";
import { Orientation, StackPanel } from "../SVGCompositor/widgets/StackPanel";
import { TextWidget } from "../SVGCompositor/widgets/TextWidget";
import { GraphNode } from "./GraphNode";
import { TriggerNode, TriggerType } from "./TriggerNode";
import { ActionNode } from "./ActionNode";
import { TextInputWidget } from "../SVGCompositor/widgets/TextInputWidget";
import { Line } from "../SVGCompositor/Line";
import { LineEnd } from "../SVGCompositor/widgets/LineEnd";
import { RGBColor } from "../SVGCompositor/StyleHelper";
import { GraphConnectorService, IGraphConnectorService } from "./GraphConnectorService";
import { Connector, ConnectorDirection, ConnectorType } from "./Connector";
import { IRGBStudioAPI, LightingConfig } from "../RGBStudioAPI";
import { Widget } from "../SVGCompositor/Widget";

export interface IGraphEditorService {
	createTriggerNode(triggerType: TriggerType): void;
	createActionNode(name: string): void;
	AddTriggerActionEdge(trigger: TriggerNode, action: ActionNode): void;
	ApplyConfig(): void;
}

interface TriggerActionEdge {
	trigger: TriggerNode;
	action: ActionNode;
}

export class GraphEditor implements IGraphEditorService {
	private compositor: SVGCompositor;
	private graph_nodes: GraphNode[];
	private tool_window: ToolWindow;
	private trigger_type: TriggerType[];
	private trigger_display_sp!: StackPanel;
	private trigger_action_edges: TriggerActionEdge[];
	private _graphConnectorService: IGraphConnectorService;
	private _nextId: number;
	private readonly _rgbStudioApi: IRGBStudioAPI;
	

	constructor(compositor: SVGCompositor, tool_window: ToolWindow, rgbStudioApi: IRGBStudioAPI) {
		this.tool_window = tool_window;
		this.compositor = compositor;
		this.graph_nodes = [];
		this.trigger_type = [];
		this.trigger_action_edges = [];
		this._graphConnectorService = new GraphConnectorService(this);
		this._nextId = 0;
		this._rgbStudioApi = rgbStudioApi;
		

		this.compositor.add(this.CreateTriggerWindow());
		this.compositor.add(this.CreateActionCreatorWindow());
		this.compositor.add(this.CreateAdministrationWindow());
		

	}

	private CreateTriggerWindow(): Widget {
		this.trigger_display_sp = CW(StackPanel, { orientation: Orientation.VERTICAL, item_spacing: 10 },
			CW(TextWidget, { text: "Available nodes", classes: ["click-through"] })
		);
		let padded_container = CW(PaddedContainer, { padding: padding(10), background: { classes: ["node-toolbox"] } },
			this.trigger_display_sp
		);

		let dragifier = new Dragifier(padded_container);
		padded_container.Clicked.add_listener((ev) => {
			dragifier.drag(ev);
		})

		return padded_container;
    }

	private CreateActionCreatorWindow(): Widget {
		let actionCreator = CW(StackPanel, { orientation: Orientation.VERTICAL, item_spacing: 10 },
			CW(TextWidget, { text: "Create event node", classes: ["click-through"] })
		);

		let paddedActionCreatorContainer = CW(PaddedContainer, { padding: padding(10), background: { classes: ["node-toolbox"] } },
			actionCreator
		);
		let dragifier = new Dragifier(paddedActionCreatorContainer);
		paddedActionCreatorContainer.Clicked.add_listener((ev) => {
			dragifier.drag(ev);
		});

		let inputWidget = actionCreator.add(CW(TextInputWidget, { width: 150 }));

		let button = actionCreator.add(CW(PaddedContainer, { padding: padding(5), background: { classes: ["debug-button"] } },
			CW(TextWidget, { text: "Create" })
		));

		button.Clicked.add_listener((ev) => {
			this.createActionNode(inputWidget.TextValue);
		});

		return paddedActionCreatorContainer;
	}

	private CreateAdministrationWindow(): Widget {
		let button = CW(PaddedContainer, { padding: padding(5), background: { classes: ["debug-button"] } },
			CW(TextWidget, { text: "Apply changes" })
		);

		let administrationWindow = CW(PaddedContainer, { padding: padding(10), background: { classes: ["node-toolbox"] } },
			CW(StackPanel, { orientation: Orientation.VERTICAL, item_spacing: 10 },
				CW(TextWidget, { text: "Administration", classes: ["click-through"] }),
				button
			)
		);

		let dragifier = new Dragifier(administrationWindow);
		administrationWindow.Clicked.add_listener((ev) => {
			dragifier.drag(ev);
		});

		button.Clicked.add_listener((ev) => {
			this.ApplyConfig();
		});

		return administrationWindow;
    }

    AddTriggerActionEdge(trigger: TriggerNode, action: ActionNode): void {
		console.log(trigger);
		console.log(action);
		this.trigger_action_edges.push({
			trigger: trigger,
			action: action
		});
		let line = new Line({ x: 0, y: 0 }, { x: 0, y: 0 }, { stroke: RGBColor.from_bytes(0, 0, 0) });
		trigger.addLineEndToSource(line.start);
		action.addLineEndToTarget(line.end);
		this.compositor.add_line(line);
    }

    createActionNode(name: string): void {
		let actionNode = new ActionNode(this.compositor, name, true, this._graphConnectorService);
		this.graph_nodes.push(actionNode);
		this.tool_window.update();
    }

	createTriggerNode(triggerType: TriggerType): void {
		let node = TriggerNode.from_trigger_type(this.compositor, (this._nextId++).toString(), triggerType, true, false, this._graphConnectorService);
		this.graph_nodes.push(node);
		this.tool_window.update();
    }

	public add_trigger_type(trigger_type: TriggerType) {
		this.trigger_type.push(trigger_type);

		TriggerNode.from_trigger_type(this.trigger_display_sp, "-1", trigger_type, false, true, this._graphConnectorService);
		let button = CW(PaddedContainer, { padding: padding(5), background: { classes: ["debug-button"] } },
			CW(TextWidget, {text: "Add"})
		);
		button.Clicked.add_listener((ev) => {
			this.createTriggerNode(trigger_type);
		})
		this.trigger_display_sp.add(button);

		this.tool_window.update();
	}

	public ApplyConfig() {
		let config: LightingConfig = {
			triggerInstances: [],
			actions: [],
			triggerActionEdges: []
		};
		this.graph_nodes.forEach(graphNode => {
			if (graphNode instanceof TriggerNode) {
				config.triggerInstances.push({
					instanceId: graphNode.UID,
					triggerId: graphNode.TriggerType.name,
					attributes: graphNode.SerializeAttributes()
				});
			} else if (graphNode instanceof ActionNode) {
				config.actions.push(graphNode.name)
			}
		});

		this.trigger_action_edges.forEach(trigger_action_edge => {
			config.triggerActionEdges.push({
				triggerId: trigger_action_edge.trigger.UID,
				actionName: trigger_action_edge.action.name
			});
		})
		this._rgbStudioApi.ApplyConfig(config);
    }
}