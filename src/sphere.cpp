#include "sphere.hpp"
#include "ray.hpp"
#include <cassert>
#include <cmath>

// compute the discriminant of quadratic equation
// Ax^2 + Bx + C = 0
static inline graphics::coordinate_type
getDiscriminant(graphics::coordinate_type A,
                graphics::coordinate_type B,
                graphics::coordinate_type C)
{
  return B * B - 4 * A * C;
}

namespace graphics {

Vector3
Sphere::computeNormal(coordinate_type t, Ray ray)
{
  Point positon = ray.source() + t * ray.direction();
  Vector3 gradient = (positon - center_) / radius_;
  if (scalarProduct(gradient, ray.direction()) > 0) {
    return -gradient;
  } else {
    return gradient;
  }
}

intersect_type
Sphere::hit(const Ray& ray,
            coordinate_type lowerbound,
            coordinate_type upperbound)
{
  assert(lowerbound >= 0);
  assert(lowerbound <= upperbound);

  // coefficients
  coordinate_type A = scalarProduct(ray.direction(), ray.direction());
  coordinate_type B =
    2 * scalarProduct(ray.direction(), ray.source() - center_);
  coordinate_type C =
    scalarProduct(ray.source() - center_, ray.source() - center_) -
    radius_ * radius_;

  assert(A > 0);

  coordinate_type discriminant = getDiscriminant(A, B, C);

  if (discriminant < 0) {
    return std::nullopt;
  } else if (discriminant > 0) {
    // two roots
    coordinate_type root = std::sqrt(discriminant);
    coordinate_type x1 = (-B - root) / (2 * A);
    coordinate_type x2 = (-B + root) / (2 * A);

    if (x1 < x2) {
      if (x1 <= upperbound && x1 >= lowerbound) {
        return std::pair{ x1, computeNormal(x1, ray) };
      } else {
        if (x2 <= upperbound && x2 >= lowerbound) {
          return std::pair{ x2, computeNormal(x1, ray) };
        } else {
          return std::nullopt;
        }
      }
    } else {
      if (x2 <= upperbound && x2 >= lowerbound) {
        return std::pair{ x2, computeNormal(x2, ray) };
      } else {
        if (x1 <= upperbound && x1 >= lowerbound) {
          return std::pair{ x1, computeNormal(x1, ray) };
        } else {
          return std::nullopt;
        }
      }
    }
  } else {
    coordinate_type x = (-B / 2) / A;
    if (x <= upperbound && x >= lowerbound) {
      return std::pair{ x, computeNormal(x, ray) };
    } else {
      return std::nullopt;
    }
  }
}

BoundingBox
Sphere::boundingbox() const
{
  Point first = center_ - Point{ radius_, radius_, radius_ };
  Point second = center_ + Point{ radius_, radius_, radius_ };
  return { first, second };
}

}
