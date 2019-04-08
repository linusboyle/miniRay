#ifndef SURFACE_CPP
#define SURFACE_CPP

#include "color.hpp"
#include "vector.hpp"

#include <optional>

namespace graphics {

class Ray;

struct BoundingBox
{
  Point first;
  Point second;
};

// t and uNormal
using intersect_type = std::optional<std::pair<coordinate_type, Vector3>>;

class Surface
{
  // TODO: extend to pattern
  RGBColor color_;
  bool reflective;

public:
  Surface(const RGBColor& color, bool reflective)
    : color_(color)
    , reflective(reflective)
  {}

  RGBColor color() const { return color_; }
  bool isReflective() const { return reflective; }

  virtual ~Surface() = 0;
  virtual intersect_type hit(const Ray& ray,
                             coordinate_type lowerbound,
                             coordinate_type upperbound) = 0;
  virtual BoundingBox boundingbox() const = 0;
};
}
#endif /* ifndef SURFACE_CPP */
