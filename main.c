#include <stdio.h>

int main()
{
    char buf[256];
    for (int i = 0; i < 60; ++i)
    {
        snprintf(buf, sizeof(buf), "output-%03d.ppm", i);
        const char *output_path = buf;
        FILE *f = fopen(output_path, "wb");

        int width = 16 * 60;
        int height = 9 * 60;
        fprintf(f, "P6\n");
        fprintf(f, "%d %d\n", width, height);
        fprintf(f, "255\n");

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (((y + i) / 60) % 2)
                {
                    fputc(0xFF, f);
                    fputc(0xFF, f);
                    fputc(0xFF, f);
                }
                else
                {
                    fputc(0xC3, f);
                    fputc(0x49, f);
                    fputc(0x46, f);
                }
            }
        }

        fclose(f);
        printf("Generated %s\n", output_path);
    }
    return 0;
}