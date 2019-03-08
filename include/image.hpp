#ifndef IMAGE_CPP
#define IMAGE_CPP

#include "color.hpp"

namespace graphics {
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

        void setpixel(unsigned int x, unsigned int y, RGBColor color); 
        void fillcolor(RGBColor color);

        void drawline(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, RGBColor color);

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
