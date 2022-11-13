export default class CsvReader {
	constructor() {

	}

	ReadCsvAndTransform<T extends Record<string, any>>(data: string, transformers: {[P in keyof T]: (val: string | undefined) => T[P]}): T[] {
		return this.ReadCsvRaw(data)
			.map(obj => Object.fromEntries(
				Object.entries(transformers)
					.map(([key, transformer]) => [key, transformer(obj[key])])
				) as T
			);
	}

	ReadCsvRaw(data: string): Record<string,string>[] {
		let rows = data.split(/\r?\n/g);
		let headers = rows[0].split(",");
		return rows.slice(1).map(row => {
			let rowObj: Record<string, string> = {};
			let cells = row.split(",");
			if (cells.length != headers.length) {
				throw new Error("Row header length mismatch");
			}
			cells.forEach((cell, columnIndex) => {
				rowObj[headers[columnIndex]] = cell;
			});
			return rowObj;
		})
	}
}