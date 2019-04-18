#ifndef COLOR_HPP
#define COLOR_HPP

#include "vector.hpp"

namespace graphics {
class RGBColor {
  Vector3 rgb_;

  double clamp(double color) const {
    // trim the illegal range
    return color < 0 ? 0 : color > 1 ? 1 : color;
  }

  unsigned char transform(double color) const {
    // gamma correction
    return static_cast<unsigned char>(std::pow(clamp(color), 1 / 2.2) * 255 +
                                      0.5);
  }

public:
  RGBColor(int r, int g, int b) : rgb_(r / 255.0, g / 255.0, b / 255.0) {}
  RGBColor(double r, double g, double b) : rgb_(r, g, b) {}
  RGBColor(Vector3 color) : rgb_(color) {}

  unsigned char r() const { return transform(rgb_(0)); }
  unsigned char g() const { return transform(rgb_(1)); }
  unsigned char b() const { return transform(rgb_(2)); }

  friend RGBColor operator+(const RGBColor &lhs, const RGBColor &rhs);
  friend RGBColor operator-(const RGBColor &lhs, const RGBColor &rhs);
  friend RGBColor operator*(const RGBColor &lhs, const RGBColor &rhs);
  friend RGBColor operator*(double lhs, const RGBColor &rhs);
};

bool operator==(const RGBColor &lhs, const RGBColor &rhs);
} // namespace graphics
#endif /* ifndef COLOR_HPP */
