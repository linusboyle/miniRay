#include "shading.hpp"
#include <algorithm>
#include <cmath>

namespace graphics {

    RGBColor ShadingPolicy::Lambertian(RGBColor cDiffuse, coordinate_type intensity, Vector3 uNormal, Vector3 lDirection) {
        return std::max(0.0, scalarProduct(uNormal,normalize(lDirection))) * intensity * cDiffuse;
    }

    RGBColor ShadingPolicy::BlinnPhong(RGBColor cSpecular, coordinate_type intensity, Vector3 uNormal, Vector3 lDirection, Vector3 vDirection, coordinate_type phongExponent) {
        Vector3 ulDirection = normalize(lDirection);
        Vector3 uvDirection = normalize(vDirection);
        Vector3 h = normalize(uvDirection + ulDirection);

        return std::max(0.0, std::pow(scalarProduct(uNormal, h), phongExponent)) * intensity * cSpecular;
    }

    RGBColor ShadingPolicy::Ambient(RGBColor cAmbient, coordinate_type aIntensity) {
        return aIntensity * cAmbient;
    }
}
