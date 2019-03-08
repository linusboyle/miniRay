#ifndef IMAGE_CPP
#define IMAGE_CPP

#include <vector>

namespace graphics {
    class RGBColor;

    struct Height {
        unsigned int value;
        explicit Height(unsigned int val): value(val) {}
        template <class Archive>
        void serialize(Archive & archive)
        {
            archive( value );
        }
    };

    struct Width {
        unsigned int value;
        explicit Width(unsigned int val): value(val) {}
        template <class Archive>
        void serialize(Archive & archive)
        {
            archive( value );
        }
    };

    class Image {
        std::vector<unsigned char> rgb_;
        Width width_;
        Height height_;

    public:
        Image(Width width, Height height)
            : rgb_(width.value * height.value * 3)
            , width_(width)
            , height_(height) 
        {}

        void setpixel(unsigned int x, unsigned int y, const RGBColor& color); 
        void fillcolor(const RGBColor& color);

        void drawline(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, const RGBColor& color);
        void drawcircle(unsigned int x, unsigned int y, unsigned int radius, const RGBColor& color);

        void writeout(const char* filename) const;

        unsigned int width() const {
            return width_.value;
        }

        unsigned int height() const {
            return height_.value;
        }

        template <class Archive>
        void serialize(Archive & archive)
        {
            archive( width_, height_, rgb_ );
        }
    };
}

#endif /* ifndef IMAGE_CPP */
