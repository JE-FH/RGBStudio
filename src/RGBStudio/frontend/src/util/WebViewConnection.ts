import type { IJSONRPCConnection, Json } from "./JSONRPC";
import { CSEvent } from "./CSEvent";

declare global {
	interface Window {
		chrome: {
			webview: {
				postMessage: (message: string) => void;
				addEventListener: (ev: "message", listener: (data: {
					data: Json | string
				}) => void) => void;
			}
		}
	}
}

export class WebViewConnection implements IJSONRPCConnection {
    private _on_message: CSEvent<(message: Json) => void>;
    public get on_message(): CSEvent<(message: Json) => void> {
        return this._on_message;
	}

	constructor() {
		this._on_message = new CSEvent();
		window.chrome.webview.addEventListener("message", (data) => {
			if (typeof (data.data) == "object") {
				console.log(data.data);
				this._on_message.call(data.data);
			} else {
				console.log("Received non json message: " + data.data);
			}
		});
    }

    async send_message(message: Json): Promise<void> {
		window.chrome.webview.postMessage(JSON.stringify(message));
	}
}
