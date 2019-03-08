namespace graphics {
    class Image;
    class RGBColor;

    namespace raster {
        void bresenham(Image& img, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, const RGBColor& color);
        void bresenham_circle(Image& img, int centerx, int centery, int radius, const RGBColor& color); 
    }
}
