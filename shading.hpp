#ifndef SHADING_HPP
#define SHADING_HPP

#include "color.hpp"
#include "vector.hpp"

namespace graphics {
    class ShadingPolicy {
    public:
        static RGBColor Lambertian(RGBColor cDiffuse, coordinate_type intensity, Vector3 uNormal, Vector3 lDirection);
        static RGBColor BlinnPhong(RGBColor cSpecular, coordinate_type intensity, Vector3 uNormal, Vector3 lDirection, Vector3 vDirection, coordinate_type phongExponent);
        static RGBColor Ambient(RGBColor cAmbient, coordinate_type aIntensity);
    };
}

#endif /* ifndef SHADING_HPP */
