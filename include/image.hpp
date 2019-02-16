#ifndef IMAGE_CPP
#define IMAGE_CPP

#include "color.hpp"

namespace graphics {
    struct Height {
        unsigned int value;
        Height(unsigned int val): value(val) {}
    };

    struct Width {
        unsigned int value;
        Width(unsigned int val):value(val){}
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
