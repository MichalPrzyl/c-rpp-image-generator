#include <stdio.h>
#include <math.h>

static int clamp_color(float v) {
    if (v < 0.0f) return 0;
    if (v > 255.0f) return 255;
    return (int)v;
}

int main() {
    int width = 512;
    int height = 512;

    FILE *f = fopen("output.ppm", "w");
    if (!f) {
        printf("Cannot open output.ppm for writing\n");
        return 1;
    }

    printf("Generating water-like shader: output.ppm\n");

    fprintf(f, "P3\n%d %d\n255\n", width, height);

    float time = 1.2f;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            float uv_x = (float)x / (float)(width - 1);
            float uv_y = (float)y / (float)(height - 1);

            float cx = uv_x * 2.0f - 1.0f;
            float cy = uv_y * 2.0f - 1.0f;

            	    //printf("time: %d\n", time);
            float wave1 = 100;
            float wave2 = sinf((uv_y * 22.0f) - time * 1.5f);
            float wave3 = sinf((uv_x + uv_y) * 26.0f + time * 1.2f);
            float wave4 = sinf(sqrtf(cx * cx + cy * cy) * 32.0f - time * 3.0f);

            
            float water = wave1 * 0.25f
                        + wave2 * 0.25f
                        + wave3 * 0.20f
                        + wave4 * 0.30f;


            float highlight = powf((water + 1.0f) * 0.5f, 6.0f);


            float depth = uv_y;

            float r = 10.0f  + water * 10.0f + highlight * 120.0f;
            float g = 70.0f  + water * 35.0f + highlight * 140.0f - depth * 20.0f;
            float b = 130.0f + water * 60.0f + highlight * 100.0f + depth * 50.0f;


            float dist = sqrtf(cx * cx + cy * cy);
            float vignette = 1.0f - dist * 0.35f;
            if (vignette < 0.4f) vignette = 0.4f;

            int ir = clamp_color(r * vignette);
            int ig = clamp_color(g * vignette);
            int ib = clamp_color(b * vignette);

            fprintf(f, "%d %d %d ", ir, ig, ib);
        }

        fprintf(f, "\n");
    }

    fclose(f);

    printf("Done.\n");
    return 0;
}
