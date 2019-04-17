#ifndef COLOR_HPP
#define COLOR_HPP

#include "vector.hpp"

namespace graphics {
class RGBColor
{
  Vector3 rgb_;

public:
  RGBColor(int r, int g, int b)
    : rgb_(r / 255.0, g / 255.0, b / 255.0)
  {}
  RGBColor(double r, double g, double b)
    : rgb_(r, g, b)
  {}
  RGBColor(Vector3 color)
    : rgb_(color)
  {}

  unsigned char r() const { return static_cast<unsigned char>(rgb_(0) * 255); }
  unsigned char g() const { return static_cast<unsigned char>(rgb_(1) * 255); }
  unsigned char b() const { return static_cast<unsigned char>(rgb_(2) * 255); }

  friend RGBColor operator+(const RGBColor& lhs, const RGBColor& rhs);
  friend RGBColor operator-(const RGBColor& lhs, const RGBColor& rhs);
  friend RGBColor operator*(double lhs, const RGBColor& rhs);
};

bool
operator==(const RGBColor& lhs, const RGBColor& rhs);
}
#endif /* ifndef COLOR_HPP */
