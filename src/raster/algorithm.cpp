#include "raster/algorithm.hpp"
#include "raster/pointlist.hpp"
#include "image.hpp"
#include "color.hpp"
#include <cmath>

static inline double fpart(double number) {
    if (number > 0.0) {
        return number - static_cast<int>(number);
    }
    else {
        return number - static_cast<int>(number) + 1;
    }
}

static inline int ipart(double number) {
    return static_cast<int>(number);
}

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

    void bresenham(Image& img, int x1, int y1, int x2, int y2, const RGBColor& color) {
        int deltax = std::abs(x1 - x2);
        int deltay = std::abs(y1 - y2);

        const int stepx = x1 < x2 ? 1 : x1 == x2 ? 0 : -1;
        const int stepy = y1 < y2 ? 1 : y1 == y2 ? 0 : -1;

        bool steep = false;
        if (deltay > deltax) {
            std::swap(deltax, deltay);
            steep = true;
        }

        int deviation = (deltay << 1) + deltax;

        for (int i = 0; i <= deltax; ++i) {
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

    void XiaolinWuLine(Image& img, int x1, int y1, int x2, int y2, const RGBColor& color) {
        const int deltax = std::abs(x1 - x2);
        const int deltay = std::abs(y1 - y2);
        const bool steep = deltax < deltay;

        if (steep) {
            std::swap(x1, y1);
            std::swap(x2, y2);
        }

        if (x1 > x2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        const double dx = x2 - x1;
        const double dy = y2 - y1;
        double gradient;

        if (dx == 0.0) {
            gradient = 1.0;
        } else {
            gradient = dy / dx;
        }

        double deviation = y1;

        if (steep) {
            for (int x = x1; x <= x2; ++x) {
                const int pos = ipart(deviation);
                const double fractional = fpart(deviation);
                const RGBColor bgColor = img.getpixel(pos + 1, x);
                img.setpixel(pos, x, (1.0 - fractional) * color + fractional * bgColor);
                img.setpixel(pos + 1, x, fractional * color + (1.0 - fractional) * bgColor);
                deviation += gradient;
            }
        } else {
            for (int x = x1; x <= x2; ++x) {
                const int pos = ipart(deviation);
                const double fractional = fpart(deviation);
                const RGBColor bgColor = img.getpixel(x, pos + 1);
                img.setpixel(x, pos, (1.0 - fractional) * color + fractional * bgColor);
                img.setpixel(x, pos + 1, fractional * color + (1.0 - fractional) * bgColor);
                deviation += gradient;
            }
        }
    }

    void rasterize(Image &img, const PointList& polygot, RGBColor color) {
        auto startP = *polygot.list.rbegin();

        for (const auto& endP : polygot.list) {
            bresenham(img, startP(0), startP(1), endP(0), endP(1), color);
            startP = endP;
        }
    }
}
