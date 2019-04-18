#include "shading.hpp"
#include <algorithm>
#include <cmath>

namespace graphics {

RGBColor ShadingPolicy::Lambertian(RGBColor cDiffuse, RGBColor intensity,
                                   Vector3 uNormal, Vector3 lDirection) {
  return std::max(0.0, scalarProduct(uNormal, normalize(lDirection))) *
         intensity * cDiffuse;
}

RGBColor ShadingPolicy::BlinnPhong(RGBColor cSpecular, RGBColor intensity,
                                   Vector3 uNormal, Vector3 lDirection,
                                   Vector3 vDirection,
                                   coordinate_type phongExponent) {
  Vector3 ulDirection = normalize(lDirection);
  Vector3 uvDirection = normalize(vDirection);
  Vector3 h = normalize(uvDirection + ulDirection);

  return std::pow(std::max(0.0, scalarProduct(uNormal, h)), phongExponent) *
         intensity * cSpecular;
}

RGBColor ShadingPolicy::Ambient(RGBColor cAmbient, RGBColor aIntensity) {
  return aIntensity * cAmbient;
}
} // namespace graphics
