#ifndef IMAGE_CPP
#define IMAGE_CPP

namespace graphics {
    class RGBColor;

    struct Height {
        unsigned int value;
        explicit Height(unsigned int val): value(val) {}
    };

    struct Width {
        unsigned int value;
        explicit Width(unsigned int val): value(val) {}
    };

    class Image {
        unsigned char* rgb_;
        Width width_;
        Height height_;

    public:
        Image(Width width, Height height)
            : rgb_(new unsigned char[width.value * height.value * 3])
            , width_(width)
            , height_(height) 
        {}

        ~Image() { delete []rgb_; }

        void setpixel(unsigned int x, unsigned int y, const RGBColor& color); 
        void fillcolor(const RGBColor& color);

        void drawline(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, const RGBColor& color);

        void writeout(const char* filename) const ;

        unsigned int width() const {
            return width_.value;
        }

        unsigned int height() const {
            return height_.value;
        }
    };
}

#endif /* ifndef IMAGE_CPP */
