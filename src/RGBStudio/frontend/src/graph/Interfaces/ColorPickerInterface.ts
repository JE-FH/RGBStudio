import ColorPickerAttribute from "@/components/ColorPickerAttribute.vue";
import { NodeInterface, setType } from "baklavajs";
import { markRaw } from "vue";
import { RGBColorType, RGBColor } from "@/graph/nodes/CustomNodeTypes";

export class ColorPickerInterface extends NodeInterface<RGBColor> {
	constructor(name: string) {
		super(name, RGBColor.from_bytes(255, 255, 255));
		this.setComponent(markRaw(ColorPickerAttribute));

		this.use(setType, RGBColorType)
	}
}