#include <cstdio>
#define SVPNG_OUTPUT FILE* fp
#include "svpng.h"

#include "image.hpp"
#include <cstring>

namespace graphics {
    void Image::setpixel(unsigned int x, unsigned int y, RGBColor color) {
        unsigned char* p = rgb_ + (y * width_.value + x) * 3;
        p[0] = color.R;
        p[1] = color.G;
        p[2] = color.B;
    }

    void Image::fillcolor(RGBColor color) {
        // optimization using memset
        if (color.R == color.B && color.B == color.G) {
            std::memset(rgb_, color.R, width_.value * height_.value * 3);
        } else {
            // brute-force
            for (unsigned int x = 0, width = width_.value; x < width; ++x) {
             for (unsigned int y = 0, height = height_.value; y < height; ++y) {
                 setpixel(x, y, color);
             }
            }
        }
    }

    void Image::writeout(const char* filename) const {
        auto file = std::fopen(filename, "wb");
        svpng(file, width_.value, height_.value, rgb_, 0);
        std::fclose(file);
    }
}
