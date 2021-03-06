#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "surface.hpp"

namespace graphics {
class Triangle : public Surface
{
  Point a;
  Point b;
  Point c;

  Vector3 computeNormal(Ray ray) const;

public:
  Triangle(Point a_,
           Point b_,
           Point c_,
           RGBColor color,
           bool reflective = false);

  virtual intersect_type hit(const Ray& ray,
                             coordinate_type lowerbound,
                             coordinate_type upperbound) override;
  virtual BoundingBox boundingbox() const override;
  virtual ~Triangle() override {}
};
}

#endif
