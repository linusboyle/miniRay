#ifndef COLOR_HPP
#define COLOR_HPP

#include "config.hpp"

namespace graphics {
    struct RGBColor {
        unsigned char R;
        unsigned char G;
        unsigned char B;
    };

    RGBColor operator+ (const RGBColor& lhs, const RGBColor& rhs);
    RGBColor operator- (const RGBColor& lhs, const RGBColor& rhs);
    RGBColor operator* (coordinate_type lhs, const RGBColor& rhs);
}
#endif /* ifndef COLOR_HPP */
