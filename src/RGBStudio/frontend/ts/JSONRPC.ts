import { CSEvent } from "./SVGCompositor/CSEvent";

export type Json =
    | number
    | string
    | boolean
    | {[key: string]: Json}
    | Array<Json>;

export interface IJSONRPCConnection {
    send_message(message: Json): Promise<void>;
    readonly on_message: CSEvent<(message: Json) => void>;
}

export interface Call<T> {
    id: number;
    method: string;
    param: T;
}

export class JSONRPC {
    private conn: IJSONRPCConnection;
    private next_id: number;
    private _on_call: CSEvent<(call_data: Call<Json>) => void>;
    public get on_call(): CSEvent<(call_data: Call<Json>) => void> {
        return this._on_call;
    }

    constructor(conn: IJSONRPCConnection) {
        this.conn = conn;
        this._on_call = new CSEvent();
        this.next_id = 0;
        conn.on_message.add_listener(this.message_handler.bind(this));
    }

    private message_handler(message: Json): void {
        if (
            typeof(message) != "object" ||
            message instanceof Array ||
            typeof(message["method"]) != "string" ||
            typeof(message["param"]) != "object" ||
            message["param"] instanceof Array ||
            typeof(message["id"]) != "number"
        ) {
            console.log("Received invalid formatted call");
            console.log(message);
            return;
        }
        this._on_call.call(message as unknown as Call<Json>);
    }

    public async dispatch_call(method: string, param: Json): Promise<number> {
        await this.conn.send_message({
            method,
            param,
            id: this.next_id
        });
        return this.next_id++;
    }

}