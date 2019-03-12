namespace graphics {
    class Image;
    class RGBColor;

    namespace raster {
        void bresenham(Image& img, int x1, int y1, int x2, int y2, const RGBColor& color);
        void bresenham_circle(Image& img, int centerx, int centery, int radius, const RGBColor& color);
        void XiaolinWuLine(Image& img, int x1, int y1, int x2, int y2, const RGBColor& color);
    }
}
