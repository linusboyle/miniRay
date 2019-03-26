#ifndef RASTER_ALGO_HPP
#define RASTER_ALGO_HPP

namespace graphics {
    class Image;
    class RGBColor;

    namespace raster {
        void BresenhamLine(Image& img, int x1, int y1, int x2, int y2, const RGBColor& color);
        void BresenhamCircle(Image& img, int centerx, int centery, int radius, const RGBColor& color);
        void XiaolinWuLine(Image& img, int x1, int y1, int x2, int y2, const RGBColor& color);
        void XiaolinWuCircle(Image& img, int centerx, int centery, int radius, const RGBColor& color);

        class PointList;
        void rasterize(Image& img, const PointList& polygot, RGBColor color);
    }
}

#endif