import KeyCodePickerAttribute from "@/components/KeyCodePickerAttribute.vue";
import { NodeInterface, setType } from "baklavajs";
import { markRaw } from "vue";
import { KeyCodeType } from "../nodes/CustomNodeTypes";

export class KeyCodePickerInterface extends NodeInterface<number> {
	constructor(name: string) {
		super(name, -1);
		this.setComponent(markRaw(KeyCodePickerAttribute));

		this.use(setType, KeyCodeType)
	}
}