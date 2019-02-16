#include "color.hpp"

namespace graphics {
    RGBColor operator+ (const RGBColor& lhs, const RGBColor& rhs) {
        unsigned short R = static_cast<unsigned short>(lhs.R) + static_cast<unsigned short>(rhs.R);
        if (R > 255)
            R = 255;
        unsigned short G = static_cast<unsigned short>(lhs.G) + static_cast<unsigned short>(rhs.G);
        if (G > 255)
            G = 255;
        unsigned short B = static_cast<unsigned short>(lhs.B) + static_cast<unsigned short>(rhs.B);
        if (B > 255)
            B = 255;

        return {static_cast<unsigned char>(R), static_cast<unsigned char>(G), static_cast<unsigned char>(B)};
    }

    RGBColor operator- (const RGBColor& lhs, const RGBColor& rhs) {
        short R = static_cast<short>(lhs.R) - static_cast<short>(rhs.R);
        if (R < 0)
            R = 0;
        short G = static_cast<short>(lhs.G) - static_cast<short>(rhs.G);
        if (G < 0)
            G = 0;
        short B = static_cast<short>(lhs.B) - static_cast<short>(rhs.B);
        if (B < 0)
            B = 0;

        return {static_cast<unsigned char>(R), static_cast<unsigned char>(G), static_cast<unsigned char>(B)};
    }

    RGBColor operator*(coordinate_type lhs, const RGBColor& rhs) {
        coordinate_type R = lhs * static_cast<coordinate_type>(rhs.R);
        if (R > 255)
            R = 255;
        coordinate_type G = lhs * static_cast<coordinate_type>(rhs.G);
        if (G > 255)
            G = 255;
        coordinate_type B = lhs * static_cast<coordinate_type>(rhs.B);
        if (B > 255)
            B = 255;

        return {static_cast<unsigned char>(R), static_cast<unsigned char>(G), static_cast<unsigned char>(B)};
    }
}
