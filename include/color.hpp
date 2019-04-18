#ifndef COLOR_HPP
#define COLOR_HPP

#include "vector.hpp"

namespace graphics {
class RGBColor {
  Vector3 rgb_;

  unsigned char clamp(double color) const {
    double tmp = color * 255;
    if (tmp > 255.0) {
      tmp = 255.0;
    }
    return static_cast<unsigned char>(tmp);
  }

public:
  RGBColor(int r, int g, int b) : rgb_(r / 255.0, g / 255.0, b / 255.0) {}
  RGBColor(double r, double g, double b) : rgb_(r, g, b) {}
  RGBColor(Vector3 color) : rgb_(color) {}

  unsigned char r() const { return clamp(rgb_(0)); }
  unsigned char g() const { return clamp(rgb_(1)); }
  unsigned char b() const { return clamp(rgb_(2)); }

  friend RGBColor operator+(const RGBColor &lhs, const RGBColor &rhs);
  friend RGBColor operator-(const RGBColor &lhs, const RGBColor &rhs);
  friend RGBColor operator*(const RGBColor &lhs, const RGBColor &rhs);
  friend RGBColor operator*(double lhs, const RGBColor &rhs);
};

bool operator==(const RGBColor &lhs, const RGBColor &rhs);
} // namespace graphics
#endif /* ifndef COLOR_HPP */
