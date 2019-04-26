#ifndef PLANE_HPP
#define PLANE_HPP

#include "surface.hpp"
#include "vector.hpp"

namespace graphics {
class Plane : public Surface {
  // a point and a normal vector define an (infinite) plane
  const Point p_;
  const Vector3 normal_;

  Vector3 computeNormal(Ray ray) const;

public:
  Plane(Point p, Vector3 normal, RGBColor color,
          RGBColor emission = {0, 0, 0},
        SurfaceProperty property = SurfaceProperty::DIFFUSE);

  virtual intersect_type hit(const Ray &ray, coordinate_type lowerbound,
                             coordinate_type upperbound) override;

  // TODO
  // this function is meaningless for a plane
  // There should be a method to get around this
  virtual BoundingBox boundingbox() const override;

  // the gradient is a constant regardless of position on the plane
  virtual ~Plane() override {}
};
} // namespace graphics

#endif /* ifndef PLANE_HPP */
