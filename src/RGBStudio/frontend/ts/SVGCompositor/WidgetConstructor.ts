import {Constructor} from "../util";
import { Widget } from "./Widget";
import { WidgetAtom } from "./WidgetAtom";
import { WidgetContainer } from "./WidgetContainer";
export function CreateWidget<T extends WidgetAtom, TArgs extends any[]>(ctor: new (...args: TArgs) => T, args: TArgs): T;
export function CreateWidget<T extends WidgetContainer, TArgs extends any[]>(ctor: new (...args: TArgs) => T, args: TArgs, children?: Widget[]): T;
export function CreateWidget<T extends Widget, TArgs extends any[]>(ctor: new (...args: TArgs) => T, args: TArgs, children?: Widget[]): T {
	let rv = new ctor(...args);
	if (rv instanceof WidgetContainer) {
		if (children) {
			for (let child of children) {
				rv.add(child);
			}
		}
	}
	return rv;
}

export function CreateWidget2<T extends Widget, TProps extends Record<string, any>>(
	ctor: new (props: TProps) => T,
	props: TProps,
	...children: Widget[]
): T {
	let rv = new ctor(props);
	if (rv instanceof WidgetContainer) {
		for (let child of children) {
			rv.add(child);
		}
	}
	return rv;
}