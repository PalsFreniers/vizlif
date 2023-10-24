#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#define NOB_IMPLEMENTATION
#include "nob.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAP_SIZE 256

static size_t map[MAP_SIZE][MAP_SIZE] = {0};
static uint32_t pixels[MAP_SIZE][MAP_SIZE] = {0};

int main(int c, char **v) {
        const char *program = nob_shift_args(&c, &v);

        if(c <= 0) {
                nob_log(NOB_ERROR, "No Input file provided");
                nob_log(NOB_INFO, "Usage : %s [FILE]", program);
                return 1;
        }

        const char *file = nob_shift_args(&c, &v);
        Nob_String_Builder content = {0};
        nob_log(NOB_INFO, "Reading %s", file);
        if(!nob_read_entire_file(file, &content)) return 1;

        if(content.count <= 0) return 0;
        for(size_t i = 0; i < content.count - 1; i++) {
                uint8_t x = content.items[i];
                uint8_t y = content.items[i + 1];

                map[y][x] += 1;
        }

        float max = 0;
        for(int y = 0; y < MAP_SIZE; y++) for(int x = 0; x < MAP_SIZE; x++) if(logf(map[y][x]) > max) max = logf(map[y][x]);

        for(int y = 0; y < MAP_SIZE; y++) {
                for(int x = 0; x < MAP_SIZE; x++) {
                        float t = logf(map[y][x]) / max;
                        uint32_t b = t * 255;
                        pixels[y][x] = 0xFF000000 | b | (b << 8) | (b << 16);
                }
        }

        const char *output_file = nob_temp_sprintf("%s.out.png", file);

        if(!stbi_write_png(output_file, MAP_SIZE, MAP_SIZE, 4, pixels, MAP_SIZE * sizeof(uint32_t))) {
                nob_log(NOB_ERROR, "un able to save image");
                return 1;
        }

        nob_log(NOB_INFO, "Generated %s", output_file);

        return 0;
}
