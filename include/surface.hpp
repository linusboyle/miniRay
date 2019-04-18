#ifndef SURFACE_CPP
#define SURFACE_CPP

#include "color.hpp"
#include "vector.hpp"

#include <optional>

namespace graphics {

class Ray;

struct BoundingBox {
  Point first;
  Point second;
};

// t and uNormal
using intersect_type = std::optional<std::pair<coordinate_type, Vector3>>;

enum class SurfaceProperty {
  DIFFUSE,
  REFLECTIVE, // specular
  REFRACTIVE  // dielectric
};

class Surface {
  // TODO: extend to pattern
  RGBColor color_;
  SurfaceProperty property_;

public:
  Surface(const RGBColor &color, SurfaceProperty p)
      : color_(color), property_(p) {}

  RGBColor color() const { return color_; }
  SurfaceProperty property() const { return this->property_; }

  virtual ~Surface();
  virtual intersect_type hit(const Ray &ray, coordinate_type lowerbound,
                             coordinate_type upperbound) = 0;
  virtual BoundingBox boundingbox() const = 0;
};
} // namespace graphics
#endif /* ifndef SURFACE_CPP */
