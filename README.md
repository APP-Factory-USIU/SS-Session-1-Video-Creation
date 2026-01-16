# 🎬 PPM Video Generator

A recreational coding project exploring the simplicity of the **PPM (Portable Pixel Map)** image format.

This project demonstrates how to generate raw image data using C/C++ without external graphics libraries, and how to stitch those frames into a video using FFmpeg.

## 🧐 What is this?

In modern programming, we often rely on heavy libraries (OpenCV, SDL, OpenGL) just to put a pixel on the screen. But what if we want to understand how digital images actually work?

This project goes back to basics:
1.  **Generate Images:** We write text/binary data to a file following the [PPM P3 Specification](https://netpbm.sourceforge.net/doc/ppm.html).
2.  **Create Animation:** We generate sequential frames (e.g., `frame001.ppm`, `frame002.ppm`).
3.  **Render Video:** We use **FFmpeg** to encode those massive, uncompressed text files into a compressed `.mp4` video.

## 🛠️ Prerequisites

To run this project, you need two things installed and added to your system PATH:

### 1. C/C++ Compiler
You need a compiler to build the generator code.
* **Windows:** [MinGW-w64 via WinLibs](https://winlibs.com/)
* **Linux:** `sudo apt install build-essential` (GCC) or `sudo apt install clang`

### 2. FFmpeg
You need this to convert the image sequence into a video file.
* **Download:** [FFmpeg.org](https://www.ffmpeg.org/download.html)
* **Note:** Ensure `ffmpeg` is accessible from your terminal.

## 🚀 Usage

### Step 1: Compile the Code
Open your terminal in the project directory and compile the C/C++ file.

**Using GCC:**
```bash
g++ main.cpp -o renderer
# or for C
gcc main.c -o renderer

```

### Step 2: Generate the Frames

Run the executable. This will flood your folder with `.ppm` files.
*(Warning: These files are uncompressed and can be large!)*

```bash
./renderer
# On Windows: renderer.exe

```

### Step 3: Stitch into Video

Use FFmpeg to combine the generated frames into an MP4 file.

```bash
ffmpeg -framerate 30 -i output-%03d.ppm -c:v libx264 -pix_fmt yuv420p output.mp4

```

or

```bash
ffmpeg -i output-%03d.ppm -r 60 output.mp4

```

**Command Breakdown:**

* `-framerate 30`: Sets the video to 30 frames per second.
* `-i output-%03d.ppm`: Tells FFmpeg to look for files named `output-001.ppm`, `output-002.ppm`, etc.
* `-c:v libx264`: Uses the H.264 codec (standard for MP4).
* `-pix_fmt yuv420p`: Ensures compatibility with standard media players (like QuickTime/Windows Media Player).

### Step 4: Cleanup

Once you have your `output.mp4`, you can delete the `.ppm` files to free up space.

```bash
# Linux/Mac
rm *.ppm

# Windows
del *.ppm

```

## 📖 The PPM Format (Brief)

We are likely using the **P3** format (ASCII based), which looks like this:

```text
P3           # Magic Number (Format type)
3 2          # Width Height
255          # Max Color Value
255 0 0      # Red Pixel
0 255 0      # Green Pixel
0 0 255      # Blue Pixel
255 255 0    # Yellow Pixel
255 255 255  # White Pixel
0 0 0        # Black Pixel

```

It is incredibly inefficient (storing numbers as text characters), but incredibly easy to read and debug!

## 🧪 Experiments to Try

1. **Gradients:** Modify the nested loops to map `x` and `y` coordinates to `r`, `g`, `b` values.
2. **Animation:** Make a circle move across the screen by changing its position based on the frame number.
3. **Resolution:** Increase the width and height and see how it impacts generation time and file size.

## YouTube link to Tsoding's video
[![Watch the video](https://img.youtube.com/vi/xNX9H_ZkfNE/maxresdefault.jpg)](https://www.youtube.com/watch?v=xNX9H_ZkfNE)

## 📄 License

This project is for educational purposes. Feel free to modify and share!
