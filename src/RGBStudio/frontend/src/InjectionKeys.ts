import type { InjectionKey } from "vue";
import type { IRGBStudioAPI } from "@/util/RGBStudioAPI";

export const RGBStudioAPISymbol: InjectionKey<IRGBStudioAPI> = Symbol("RGBStudioAPI");