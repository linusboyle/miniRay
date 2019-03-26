#ifndef COLOR_HPP
#define COLOR_HPP

namespace graphics {
    class RGBColor {
        double R;
        double G;
        double B;
    public:
        RGBColor(int r, int g, int b) : R(r / 255.0), G(g / 255.0), B(b / 255.0) {}
        RGBColor(double r, double g, double b) : R(r), G(g), B(b) {}

        unsigned char r() const {
            return static_cast<unsigned char>(R * 255);
        }
        unsigned char g() const {
            return static_cast<unsigned char>(G * 255);
        }
        unsigned char b() const {
            return static_cast<unsigned char>(B * 255);
        }

        friend RGBColor operator+ (const RGBColor& lhs, const RGBColor& rhs);
        friend RGBColor operator- (const RGBColor& lhs, const RGBColor& rhs);
        friend RGBColor operator* (double lhs, const RGBColor& rhs);
    };

    bool operator==(const RGBColor& lhs, const RGBColor& rhs);
}
#endif /* ifndef COLOR_HPP */
