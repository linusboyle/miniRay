#include "raster/algorithm.hpp"
#include "raster/pointlist.hpp"
#include "image.hpp"
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

    /*
     * helper function used in drawing symmetric shapes
     */
    static inline void drawpixel4(Image& img, int centerx, int centery, int x, int y, const RGBColor& color) {
        //            |
        //    (-x, y) |  (x, y)
        //            |
        //    --------|--------
        //    (-x, -y)|  (x, -y)
        //            |
        //            |
        img.setpixel(centerx + x, centery + y, color);
        img.setpixel(centerx - x, centery - y, color);

        if (y != 0)
            img.setpixel(centerx + x, centery - y, color);
        if (x != 0)
            img.setpixel(centerx - x, centery + y, color);
    }

    static inline void drawpixel8(Image& img, int centerx, int centery, int x, int y, const RGBColor& color) {
        drawpixel4(img, centerx, centery, x, y, color);
        if (x != y) // don't draw the pixels twice
            drawpixel4(img, centerx, centery, y, x, color);
    }

    // some utils, convenient for human eyes
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

    void BresenhamLine(Image& img, int x1, int y1, int x2, int y2, const RGBColor& color) {
        int deltax = std::abs(x1 - x2);
        int deltay = std::abs(y1 - y2);

        const int stepx = x1 < x2 ? 1 : x1 == x2 ? 0 : -1;
        const int stepy = y1 < y2 ? 1 : y1 == y2 ? 0 : -1;

        bool steep = false;
        if (deltay > deltax) {
            std::swap(deltax, deltay);
            steep = true;
        }

        int deviation = - deltax;

        for (int i = 0; i <= deltax; ++i) {
            img.setpixel(x1, y1, color);

            if (steep) {
                y1 += stepy;
            } else {
                x1 += stepx;
            }

            deviation += deltay << 1;

            if (deviation > 0) {
                if (steep) {
                    x1 += stepx;
                } else {
                    y1 += stepy;
                }

                deviation -= deltax << 1;
            }

        }
    }

    void BresenhamCircle(Image& img, int centerx, int centery, int radius, const RGBColor& color) {
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
                // divide the opacity:
                // fractional is the opacity of (ypos, x); 1 - fractional for (ypos + 1, x)
                // 1 means fully transparent
                // 0 means pure color
                const int ypos = ipart(deviation);
                const double fractional = fpart(deviation);

                // these two are original colors of the accroding pixels
                // which will be mixed later
                RGBColor&& bgColor = img.getpixel(ypos, x);
                RGBColor&& bgColor2 = img.getpixel(ypos + 1, x);

                img.setpixel(ypos, x, (1.0 - fractional) * color + fractional * bgColor);
                img.setpixel(ypos + 1, x, fractional * color + (1.0 - fractional) * bgColor2);
                deviation += gradient;
            }
        } else {
            for (int x = x1; x <= x2; ++x) {
                // likewise
                const int pos = ipart(deviation);
                const double fractional = fpart(deviation);

                RGBColor&& bgColor = img.getpixel(x, pos);
                RGBColor&& bgColor2 = img.getpixel(x, pos + 1);

                img.setpixel(x, pos, (1.0 - fractional) * color + fractional * bgColor);
                img.setpixel(x, pos + 1, fractional * color + (1.0 - fractional) * bgColor2);
                deviation += gradient;
            }
        }
    }

    void rasterize(Image& img, const PointList& polygon, RGBColor color) {
        auto startP = *polygon.list.rbegin();

        for (const auto& endP : polygon.list) {
            img.drawline(startP(0), startP(1), endP(0), endP(1), color);
            startP = endP;
        }
    }

    // draw a circle with anti aliasing
    // NOTE: not for drawing ellipse
    void XiaolinWuCircle(Image& img, int centerx, int centery, int radius, const RGBColor& color) {
        double x = radius;

        for (int y = 0; y < x; ++y) {
            x = std::sqrt(radius * radius - y * y);

            double fractional = fpart(x);

            int xpos = ipart(x);

            RGBColor&& bgColor = img.getpixel(centerx + xpos, centery + y);
            RGBColor&& bgColor2 = img.getpixel(centerx + xpos + 1, centery + y);

            RGBColor&& newcolor = (1.0 - fractional) * color  + fractional * bgColor;
            RGBColor&& newcolor2 = fractional * color + (1.0 - fractional) * bgColor2;

            drawpixel8(img, centerx, centery, xpos, y, newcolor);
            drawpixel8(img, centerx, centery, xpos + 1, y, newcolor2);
        }
    }
}
