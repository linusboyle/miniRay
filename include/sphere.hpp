#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "surface.hpp"

namespace graphics {
class Sphere : public Surface {
  Point center_;
  coordinate_type radius_;
  Vector3 computeNormal(coordinate_type t, Ray ray);

public:
  Sphere(Point center, coordinate_type radius, RGBColor color,
         SurfaceProperty p = SurfaceProperty::DIFFUSE)
      : Surface(color, p), center_(center), radius_(radius) {}
  virtual intersect_type hit(const Ray &ray, coordinate_type lowerbound,
                             coordinate_type upperbound) override;
  virtual BoundingBox boundingbox() const override;
  virtual ~Sphere() override {}
};
} // namespace graphics
#endif /* ifndef SPHERE_HPP */
