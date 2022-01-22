const fs = require("fs/promises")
const path = require("path");

async function get_ts_files(directory) {
	let entries = await fs.readdir(directory);

	return (await Promise.all(entries.map(async (entry) => {
		let stat = await fs.stat(path.join(directory, entry));
		if (stat.isDirectory()) {
			let sub_files = await get_ts_files(path.join(directory, entry));
			return sub_files;
		} else {
			if (entry.endsWith(".ts")) {
				return [path.join(directory, entry)]
			} else {
				return [];
			}
		}
	}))).flat();
}

get_ts_files("ts/")
	.then((files) => {
		files.forEach((file) => {
			console.log(file.replaceAll("\\", "/") + " \\");
		})
	});