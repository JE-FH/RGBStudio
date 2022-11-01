import { JSONRPC } from "./JSONRPC";
import { CSEvent } from "./SVGCompositor/CSEvent";
import { WebViewConnection } from "./WebViewConnection";

export interface AddedTriggerEvent {
    fields: Record<string, {
        required: boolean;
        name: string;
        type: string;
    }>;
    name: string;
}

class RGBStudioAPI {
    private _rpc: JSONRPC;

    private _onAddedTrigger: CSEvent<(addedTrigger: AddedTriggerEvent) => void>;
    public get OnAddedTrigger(): CSEvent<(addedTrigger: AddedTriggerEvent) => void> {
        return this._onAddedTrigger;
    }

    constructor() {
        this._rpc = new JSONRPC(new WebViewConnection());
        this._onAddedTrigger = new CSEvent();
    }

    public async Ready() {
        await this._rpc.dispatch_call("ready", {});
    }
}