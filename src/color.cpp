#include "color.hpp"

namespace graphics {
    RGBColor operator+ (const RGBColor& lhs, const RGBColor& rhs) {
        double r_ = lhs.R + rhs.R;
        if (r_ > 1.0)
            r_ = 1.0;
        double g_ = lhs.G + rhs.G;
        if (g_ > 1.0)
            g_ = 1.0;
        double b_ = lhs.B + rhs.B;
        if (b_ > 1.0)
            b_ = 1.0;

        return {r_, g_, b_};
    }

    RGBColor operator- (const RGBColor& lhs, const RGBColor& rhs) {
        double r_ = lhs.R - rhs.R;
        if (r_ < 0.0)
            r_ = 0.0;
        double g_ = lhs.G - rhs.G;
        if (g_ < 0.0)
            g_ = 0.0;
        double b_ = lhs.B - rhs.B;
        if (b_ < 0.0)
            b_ = 0.0;

        return {r_, g_, b_};
    }

    RGBColor operator*(double lhs, const RGBColor& rhs) {
        double r_ = lhs * rhs.R;
        if (r_ > 1.0)
            r_ = 1.0;
        double g_ = lhs * rhs.G;
        if (g_ > 1.0)
            g_ = 1.0;
        double b_ = lhs * rhs.B;
        if (b_ > 1.0)
            b_ = 1.0;

        return {r_, g_, b_};
    }
}