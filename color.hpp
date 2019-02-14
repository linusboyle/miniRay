#ifndef COLOR_HPP
#define COLOR_HPP

namespace graphics {
    struct RGBColor {
        unsigned char R;
        unsigned char G;
        unsigned char B;
    };

    RGBColor operator+ (const RGBColor& lhs, const RGBColor& rhs);
    RGBColor operator- (const RGBColor& lhs, const RGBColor& rhs);

}
#endif /* ifndef COLOR_HPP */
