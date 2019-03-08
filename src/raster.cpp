#include "raster.hpp"
#include "image.hpp"
#include <cmath>

namespace graphics::raster {
    static inline void drawpixel4(Image& img, int centerx, int centery, int x, int y, const RGBColor& color) {
        //            |
        //    (-x, y) |  (x, y)
        //            |
        //    --------|--------
        //    (-x, -y)|  (x, -y)
        //            |
        //            |
        img.setpixel(centerx + x, centery + y, color);
        img.setpixel(centerx + x, centery - y, color);
        img.setpixel(centerx - x, centery + y, color);
        img.setpixel(centerx - x, centery - y, color);
    }

    static inline void moveRight(int& x, int&, int& deviation) {
        x++;
        deviation += (x << 1) + 1;
    }

    static inline void moveBelow(int&, int& y, int& deviation) {
        y--;
        deviation -= (y << 1) - 1;
    }

    static inline void moveRightBelow(int& x, int& y, int& deviation) {
        x++;
        y--;
        deviation += ((x - y) << 1) + 2;
    }

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

    void bresenham_circle(Image& img, int centerx, int centery, int radius, const RGBColor& color) {
        // start from (0,r) to (r,0)
        int offset_x = 0;
        int offset_y = radius;

        int deviation= (1 - radius) << 1;

        constexpr int limit = 0;
        while (offset_y >= limit) {
            drawpixel4(img, centerx, centery, offset_x, offset_y, color);

            if (deviation < 0) {
                int delta = ((deviation + offset_y) << 1) + 1;
                if (delta <= 0) {
                    moveRight(offset_x, offset_y, deviation);
                } else {
                    moveRightBelow(offset_x, offset_y, deviation);
                }
            } else if (deviation > 0) {
                int delta = ((deviation - offset_y) << 1) - 1;
                if (delta <= 0) {
                    moveRightBelow(offset_x, offset_y, deviation);
                } else {
                    moveBelow(offset_x, offset_y, deviation);
                }
            } else {
                moveRight(offset_x, offset_y, deviation);
            }
        }
    }
}
