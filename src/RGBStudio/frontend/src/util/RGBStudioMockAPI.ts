import { CSEvent } from "./CSEvent";
import type { EffectDescription, TriggerDescription, IRGBStudioAPI, LightingConfig } from "./RGBStudioAPI";

export default class RGBStudioMockAPI implements IRGBStudioAPI {
	private _triggers: TriggerDescription[];
	private _effects: EffectDescription[];

	OnAddedTrigger: CSEvent<(addedTrigger: TriggerDescription) => void>;
    OnAddedEffect: CSEvent<(addedTrigger: EffectDescription) => void>;
	
	constructor(triggers: TriggerDescription[], effects: EffectDescription[]) {
		this.OnAddedTrigger = new CSEvent();
		this.OnAddedEffect = new CSEvent();
		this._triggers = triggers;
		this._effects = effects;
	}
	
	async ApplyConfig(config: LightingConfig): Promise<void> {
		//TODO: Could check if the triggers and effects are valid
		console.log("Applied config");
		console.log(config);
	}
	
	async Ready(): Promise<void> {
		await new Promise((resolve) => setTimeout(resolve, 1000));
		let randomOrderEvents: (["trigger", TriggerDescription] | ["effect", EffectDescription])[] = [];
		this._triggers.map<["trigger", TriggerDescription]>(x => ["trigger", x]).forEach(x => randomOrderEvents.push(x));
		this._effects.map<["effect", EffectDescription]>(x => ["effect", x]).forEach(x => randomOrderEvents.push(x));

		randomOrderEvents = randomOrderEvents.map(x => ({x, randomNumber: Math.random()}))
			.sort((a, b) => a.randomNumber - b.randomNumber)
			.map(x => x.x);

		for (let event of randomOrderEvents) {
			await new Promise((resolve) => setTimeout(resolve, Math.random() * 100));
			if (event[0] == "trigger") {
				this.OnAddedTrigger.call(event[1]);
			} else {
				this.OnAddedEffect.call(event[1]);
			}
		}
		
	}
}