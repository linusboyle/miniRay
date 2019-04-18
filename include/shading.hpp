#ifndef SHADING_HPP
#define SHADING_HPP

#include "color.hpp"
#include "vector.hpp"

namespace graphics {
class ShadingPolicy {
public:
  static RGBColor Lambertian(RGBColor cDiffuse, RGBColor intensity,
                             Vector3 uNormal, Vector3 lDirection);
  static RGBColor BlinnPhong(RGBColor cSpecular, RGBColor intensity,
                             Vector3 uNormal, Vector3 lDirection,
                             Vector3 vDirection, coordinate_type phongExponent);
  static RGBColor Ambient(RGBColor cAmbient, RGBColor aIntensity);
};
} // namespace graphics

#endif /* ifndef SHADING_HPP */
