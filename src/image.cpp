#include <cstdio>
#define SVPNG_OUTPUT FILE* fp
#include "svpng.h"

#include "image.hpp"
#include "raster.hpp"
#include "color.hpp"
#include <cstring>

namespace graphics {
    void Image::setpixel(unsigned int x, unsigned int y, const RGBColor& color) {
        const unsigned int base = (y * width_ + x) * 3;
        rgb_[base] = static_cast<unsigned char>(255 * color.R);
        rgb_[base + 1] = static_cast<unsigned char>(255 * color.G);
        rgb_[base + 2] = static_cast<unsigned char>(255 * color.B);
    }

    void Image::fillcolor(const RGBColor& color) {
        // optimization using memset
        if (color.R == color.B && color.B == color.G) {
            std::memset(rgb_.data(), static_cast<unsigned char>(255 * color.R), width_ * height_ * 3);
        } else {
            // brute-force
            for (unsigned int x = 0; x < width_; ++x) {
                for (unsigned int y = 0; y < height_; ++y) {
                    setpixel(x, y, color);
                }
            }
        }
    }

    void Image::writeout(const char* filename) const {
        auto file = std::fopen(filename, "wb");
        svpng(file, width_, height_, rgb_.data(), 0);
        std::fclose(file);
    }

    void Image::drawline(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, const RGBColor& color) {
        raster::bresenham(*this, x1, y1, x2, y2, color);
    }
}
