const typescript = require('@rollup/plugin-typescript');
const {readFileSync} = require("fs");
const {join} = require("path");
const tsc = require("typescript");
const nodeResolve = require('rollup-plugin-node-resolve');
const commonjs = require("rollup-plugin-commonjs");

const FILES = ["editor.m.ts"];

export default FILES.map(file_name => ({
	input: join(__dirname,  'ts/' + file_name),
	output: {
		dir: '../build/script',
		format: "cjs",
		sourcemap: true
	},
	plugins: [
		nodeResolve({}),
		commonjs(),
		typescript({tsconfig: join(__dirname, "tsconfig.json")}),
	]
}));