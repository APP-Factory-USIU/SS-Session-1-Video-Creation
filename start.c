#include <stdio.h>

int main()
{
    char buf[256];

    // Generate 60 frames for animation
    for (int i = 0; i < 60; i++)
    {
        // Format filename: output-001.ppm, output-002.ppm, etc.
        snprintf(buf, sizeof(buf), "output-%03d.ppm", i);
        const char *output_path = buf;

        // Open in write-binary mode ("wb") for P6 format
        FILE *f = fopen(output_path, "wb");

        int width = 16 * 60;
        int height = 9 * 60;

        fprintf(f, "P6\n");                   // file format P6 (Binary)
        fprintf(f, "%d %d\n", width, height); // Dimensions
        fprintf(f, "255\n");                  // Max color

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                // Calculate moving checkerboard pattern based on frame 'i'
                if (((x + i) / 60 + (y + i) / 60) % 2)
                {
                    // Pixel 1: Black (R, G, B)
                    fputc(0x00, f);
                    fputc(0x00, f);
                    fputc(0x00, f);
                }
                else
                {
                    // Pixel 2: Custom Color (R, G, B)
                    fputc(0x42, f);
                    fputc(0x5C, f);
                    fputc(0x29, f);
                }
            }
        }

        fclose(f);
        printf("Generated %s\n", output_path);
    }
}