const fs = require("fs");

// Standard 16x9 aspect ratio
const w = 16 * 60;
const h = 9 * 60;

const header = `P6\n${w} ${h}\n255\n`;

// Allocate 3 bytes (RGB) per pixel
const buffer = Buffer.alloc(w * h * 3);

let offset = 0;

for (let y = 0; y < h; ++y) {
  for (let x = 0; x < w; ++x) {
    // Checkerboard logic
    const check = (Math.floor(x / 60) + Math.floor(y / 60)) % 2;

    if (check) {
      buffer[offset++] = 0x00; // R
      buffer[offset++] = 0x00; // G
      buffer[offset++] = 0x00; // B
    } else {
      buffer[offset++] = 0x42; // R
      buffer[offset++] = 0x5c; // G
      buffer[offset++] = 0x29; // B
    }
  }
}

const stream = fs.createWriteStream("file.ppm");

stream.write(header);
stream.write(buffer);
stream.end();

console.log("Generated file.ppm");

/*
====================================================================
 THE BAD EXAMPLE (String Concatenation)
====================================================================

 Why do we use Buffers?

 If you use standard strings, JS treats numbers as text.
 `data += 0x42` converts the number 66 to the string "66".

 - Binary (Buffer): Writes 1 byte (0x42).
 - String (Below):  Writes 2 bytes ('6', '6').

 This bloats the file and corrupts the pixel data. You can try
 uncommenting this to see the difference:

 let data = `P6\n${w} ${h}\n255\n`;

 for (let y = 0; y < h; ++y) {
   for (let x = 0; x < w; ++x) {
     if ((Math.floor(x / 60) + Math.floor(y / 60)) % 2) {
       data += 0x00;
       data += 0x00;
       data += 0x00;
     } else {
       // This writes "669241" text, not color bytes!
       data += 0x42;
       data += 0x5c;
       data += 0x29;
     }
   }
 }
*/
