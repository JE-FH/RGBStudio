import { TextInputWidget, TextInputWidgetProps } from "./TextInputWidget";

interface FullNumberInputWidgetProps extends TextInputWidgetProps {
	initial_number: number;
}

export type NumberInputWidgetProps = Omit<FullNumberInputWidgetProps, "type">;


export class NumberInputWidget extends TextInputWidget {
	public get NumberValue(): number {
		return Number(super.TextValue);
	}

	public set NumberValue(value: number) {
		super.TextValue = value.toString();
	}

	constructor(props: NumberInputWidgetProps) {
		super({...props, type: "number"});
		this.NumberValue = props.initial_number;
	}
}