import { createCanvas, loadImage } from "https://deno.land/x/canvas/mod.ts";

const [_, dir, outputName, fps] = Deno.args;

let files = [];

for await (const file of Deno.readDir(dir)) {
	files.push(`${dir}/${file.name}`);
}

const charAspectRatio = 8.41 / 18
const height = 50;
const refImage = await loadImage(files[0]);
const width = Math.ceil(refImage.width() / refImage.height() * (1/charAspectRatio) * height);

const canvas = createCanvas(width, height);
const ctx = canvas.getContext("2d");

let encodeU32 = (n) => {
	return new Uint8Array([
		n & 255,
		(n >> 8) & 255,
		(n >> 16) & 255,
		(n >> 24) & 255
	])
}

function convertFrameToAscii(image) {	
	const map = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
	
	ctx.drawImage(image, 0, 0, width, height);
	
	let imageData = []
	let minGray = 1, maxGray = 0;
	
	for (let y = 0; y < height; ++y) {
		let imageDataLine = [];
		for (let x = 0; x < width; ++x) {
			let color = ctx.getImageData(x, y, 1, 1).data;
	
			// https://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
			let grayscale = (color[0] * 0.21 + color[1] * 0.72 + color[2] * 0.07) / 256;
			minGray = Math.min(minGray, grayscale);
			maxGray = Math.max(maxGray, grayscale);
	
			imageDataLine.push([color, grayscale]);
		}
		imageData.push(imageDataLine)
	}
	
	let setError = (x, y, error) => {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			imageData[y][x][1] += error;
		}
	}
	
	// Remap grayscale
	for (let y = 0; y < height; ++y) {
		for (let x = 0; x < width; ++x) {
			let pix = imageData[y][x];
			let grayscaleRemap = ((pix[1] - minGray) / (maxGray - minGray));
			pix[1] = grayscaleRemap;
		}
	}
	
	let frame = [];
	for (let y = 0; y < height; ++y) {
		for (let x = 0; x < width; ++x) {
			let pix = imageData[y][x];

			// Set color
			frame.push(pix[0][0]);
			frame.push(pix[0][1]);
			frame.push(pix[0][2]);

			// Choose char
			let grayscaleValue = pix[1] * map.length;
			let grayscaleIndex = Math.floor(grayscaleValue);
			frame.push((map[grayscaleIndex] ?? map[map.length - 1]).charCodeAt(0));

			// Dithering
			// https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering
			let grayscaleError = (grayscaleValue - grayscaleIndex) / map.length;
			setError(x + 1, y    , grayscaleError * 7 / 16);
			setError(x - 1, y + 1, grayscaleError * 3 / 16);
			setError(x    , y + 1, grayscaleError * 5 / 16);
			setError(x + 1, y + 1, grayscaleError * 1 / 16);
		}
	}
	return new Uint8Array(frame);
}

const file = await Deno.open(`${outputName}.celine`, { write: true, truncate: true, create: true });

files.sort();

Deno.writeSync(file.rid, encodeU32(fps));
Deno.writeSync(file.rid, encodeU32(files.length));

Deno.writeSync(file.rid, encodeU32(width));
Deno.writeSync(file.rid, encodeU32(height));

for (const filename of files) {
	console.error(filename);
	const image = await loadImage(filename);

	const ascii = convertFrameToAscii(image);
	Deno.writeSync(file.rid, ascii);
}

Deno.close(file.rid);