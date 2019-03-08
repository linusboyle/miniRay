#include "raster.hpp"
#include "image.hpp"
#include <cmath>

namespace graphics::raster {
    void bresenham(Image& img, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, const RGBColor& color) {
        int deltax = std::abs(static_cast<int>(x1) - static_cast<int>(x2));
        int deltay = std::abs(static_cast<int>(y1) - static_cast<int>(y2));

        const int stepx = x1 < x2 ? 1 : -1;
        const int stepy = y1 < y2 ? 1 : -1;

        bool steep = false;
        if (deltay > deltax) {
            std::swap(deltax, deltay);
            steep = true;
        }

        int deviation = (deltay << 1) + deltax;

        for (int i = 0; i < deltax; ++i) {
            img.setpixel(x1, y1, color);

            if (deviation > 0) {
                if (steep) {
                    x1 += stepx;
                } else {
                    y1 += stepy;
                }

                deviation -= deltax << 1;
            }

            if (steep) {
                y1 += stepy;
            } else {
                x1 += stepx;
            }

            deviation += deltay << 1;
        }
    }
}
