import { GraphNodeAttribute } from "./GraphNodeAttribute";

export class NumberAttribute extends GraphNodeAttribute {
	value: number;

	constructor(name: string, value: number) {
		super(name);
		this.value = value;
	}
}