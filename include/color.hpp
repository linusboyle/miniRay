#ifndef COLOR_HPP
#define COLOR_HPP

#include "config.hpp"

namespace graphics {
    struct RGBColor {
        double R;
        double G;
        double B;
    };

    RGBColor operator+ (const RGBColor& lhs, const RGBColor& rhs);
    RGBColor operator- (const RGBColor& lhs, const RGBColor& rhs);
    RGBColor operator* (double lhs, const RGBColor& rhs);
}
#endif /* ifndef COLOR_HPP */
