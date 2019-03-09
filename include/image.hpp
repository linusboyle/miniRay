#ifndef IMAGE_CPP
#define IMAGE_CPP

#include <vector>

namespace graphics {
    class RGBColor;

    class Image {
        std::vector<unsigned char> rgb_;
        unsigned int width_;
        unsigned int height_;

    public:
        Image(unsigned int width, unsigned int height)
            : rgb_(width * height * 3, 0)
            , width_(width)
            , height_(height) 
        {}

        void setpixel(unsigned int x, unsigned int y, const RGBColor& color); 
        void fillcolor(const RGBColor& color);

        void drawline(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, const RGBColor& color);
        void drawcircle(unsigned int x, unsigned int y, unsigned int radius, const RGBColor& color);

        void writeout(const char* filename) const;

        unsigned int width() const {
            return width_;
        }

        unsigned int height() const {
            return height_;
        }

        // for cereal to serial this picture
        template <class Archive>
        void serialize(Archive & archive)
        {
            archive( width_, height_, rgb_ );
        }

        friend bool operator==(const Image& lhs, const Image& rhs) {
            return lhs.width_ == rhs.width_ && lhs.height_ == rhs.height_ && lhs.rgb_ == rhs.rgb_;
        }
    };
}

#endif /* ifndef IMAGE_CPP */
