#include "color.hpp"

namespace graphics {
    RGBColor operator+ (const RGBColor& lhs, const RGBColor& rhs) {
        double R = lhs.R + rhs.R;
        if (R > 1.0)
            R = 1.0;
        double G = lhs.G + rhs.G;
        if (G > 1.0)
            G = 1.0;
        double B = lhs.B + rhs.B;
        if (B > 1.0)
            B = 1.0;

        return {R, G, B};
    }

    RGBColor operator- (const RGBColor& lhs, const RGBColor& rhs) {
        double R = lhs.R - rhs.R;
        if (R < 0.0)
            R = 0.0;
        double G = lhs.G - rhs.G;
        if (G < 0.0)
            G = 0.0;
        double B = lhs.B - rhs.B;
        if (B < 0.0)
            B = 0.0;

        return {R, G, B};
    }

    RGBColor operator*(double lhs, const RGBColor& rhs) {
        double R = lhs * rhs.R;
        if (R > 1.0)
            R = 1.0;
        double G = lhs * rhs.G;
        if (G > 1.0)
            G = 1.0;
        double B = lhs * rhs.B;
        if (B > 1.0)
            B = 1.0;

        return {R, G, B};
    }
}
