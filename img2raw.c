#include <stdio.h>
#include <stdint.h>
#define NOB_IMPLEMENTATION
#include "nob.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int c, char **v) {
        const char *program = nob_shift_args(&c, &v);

        if(c <= 0) {
                nob_log(NOB_ERROR, "No Input file provided");
                nob_log(NOB_INFO, "Usage : %s [FILE]", program);
                return 1;
        }

        const char *file = nob_shift_args(&c, &v);
        int x, y;
        uint32_t *pixels = (uint32_t *)stbi_load(file, &x, &y, NULL, 4);
        if(!pixels) {
                nob_log(NOB_ERROR, "Could not load file %s", file);
                return 1; 
        }
        const char *output_file = nob_temp_sprintf("%s.raw", file);
        nob_write_entire_file(output_file, pixels, sizeof(uint32_t) * x * y);
        nob_log(NOB_INFO, "Generated %s", output_file);
        return 0;
}
