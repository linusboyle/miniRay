#include "color.hpp"

namespace graphics {
RGBColor operator+(const RGBColor &lhs, const RGBColor &rhs) {
  return {lhs.rgb_ + rhs.rgb_};
}

RGBColor operator-(const RGBColor &lhs, const RGBColor &rhs) {
  return {lhs.rgb_ - rhs.rgb_};
}

RGBColor operator*(double lhs, const RGBColor &rhs) { return {lhs * rhs.rgb_}; }

RGBColor operator*(const RGBColor &lhs, const RGBColor &rhs) {
  return {mult(lhs.rgb_, rhs.rgb_)};
}

bool operator==(const RGBColor &lhs, const RGBColor &rhs) {
  // almost equal
  if (lhs.r() == rhs.r() && lhs.b() == rhs.b() && lhs.g() == rhs.g())
    return true;
  return false;
}

} // namespace graphics