const fs = require("fs/promises")
const path = require("path");

async function get_files(directory) {
	let entries = await fs.readdir(directory);

	return (await Promise.all(entries.map(async (entry) => {
		let stat = await fs.stat(path.join(directory, entry));
		if (stat.isDirectory()) {
			let sub_files = await get_files(path.join(directory, entry));
			return sub_files;
		} else {
			return [path.join(directory, entry)];
		}
	}))).flat();
}

let fileString = "";

async function main() {
	let files = await get_files("src");
	for (let i = 0; i < files.length; i++) {
		let file = files[i];
		if (i + 1 == files.length) {
			fileString += file.replaceAll("\\", "/");
		} else {
			fileString += file.replaceAll("\\", "/") + " \\\n";
        }
    }
	let makefile = `all: ../build/editor.html
frontend/dist/index.html: ${fileString}
	npm run build

../build/editor.html: frontend/dist/index.html
	node inlinehtml.js "frontend/dist/index.html" "../build/editor.html" "../frontend/dist/"
`;
	fs.writeFile("makefile", makefile);
}

main();
