import { Call, Json, JSONRPC } from "./JSONRPC";
import { CSEvent } from "./SVGCompositor/CSEvent";
import { WebViewConnection } from "./WebViewConnection";

export interface AddedTriggerEvent {
    fields: Record<string, {
        name: string;
        type: string;
    }>;
    name: string;
}

export interface AddedEffectEvent {
    fields: Record<string, {
        name: string;
        type: string;
    }>;
    name: string;
}

export interface LightingConfig {
    triggerInstances: TriggerInstanceConfig[];
    triggerActionEdges: TriggerActionEdge[];
    actionEffectEdges: ActionEffectEdge[];
    effectInstances: EffectInstanceConfig[];
}

export interface TriggerActionEdge {
    triggerInstanceId: string;
    actionName: string;
}

export interface TriggerInstanceConfig {
    instanceId: string;
    triggerId: string;
    attributes: DynamicConfigAttribute[];
}

export interface ActionEffectEdge {
    actionName: string;
    effectInstanceId: string;
}

export interface EffectInstanceConfig {
    instanceId: string;
    effectId: string;
    attributes: DynamicConfigAttribute[];
}

export interface DynamicConfigAttribute {
    name: string;
    value: string;
}


export interface IRGBStudioAPI {
    readonly OnAddedTrigger: CSEvent<(addedTrigger: AddedTriggerEvent) => void>;
    ApplyConfig(config: LightingConfig): Promise<void>;
    Ready(): Promise<void>;
}

export class RGBStudioAPI {
    private _rpc: JSONRPC;

    private _onAddedTrigger: CSEvent<(addedTrigger: AddedTriggerEvent) => void>;
    public get OnAddedTrigger(): CSEvent<(addedTrigger: AddedTriggerEvent) => void> {
        return this._onAddedTrigger;
    }

    private _onAddedEffect: CSEvent<(addedEffect: AddedEffectEvent) => void>;
    public get OnAddedEffect(): CSEvent<(addedEffect: AddedEffectEvent) => void> {
        return this._onAddedEffect;
    }

    constructor() {
        this._rpc = new JSONRPC(new WebViewConnection());
        this._onAddedTrigger = new CSEvent();
        this._onAddedEffect = new CSEvent();
        this._rpc.on_call.add_listener(this.CallHandler.bind(this));
    }

    private CallHandler(call: Call<Json>) {
        if (call.method == "AddedTrigger") {
            this.OnAddedTrigger.call(call.param as unknown as AddedTriggerEvent);
        } else if (call.method = "AddedEffect") {
            this.OnAddedEffect.call(call.param as unknown as AddedEffectEvent);
        } else {
            console.warn(`Received unknown call \"${call.method}\"`);
        }
    }

    public async ApplyConfig(config: LightingConfig) {
        console.log("applying new config");
        console.log(config);
        await this._rpc.dispatch_call("apply_config", config as unknown as Json);
    }

    public async Ready() {
        await this._rpc.dispatch_call("ready", {});
    }
}