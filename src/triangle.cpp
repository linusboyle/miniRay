#include "triangle.hpp"
#include "ray.hpp"

namespace graphics {
static coordinate_type min3(coordinate_type a, coordinate_type b,
                            coordinate_type c) {
  coordinate_type tmp = std::min(a, b);
  return std::min(tmp, c);
}

static coordinate_type max3(coordinate_type a, coordinate_type b,
                            coordinate_type c) {
  coordinate_type tmp = std::max(a, b);
  return std::max(tmp, c);
}

Triangle::Triangle(Point a_, Point b_, Point c_, RGBColor color,
                   SurfaceProperty p)
    : Surface(color, p), a(a_), b(b_), c(c_) {}

intersect_type Triangle::hit(const Ray &ray, coordinate_type lowerbound,
                             coordinate_type upperbound) {
  const Matrix<3, 3> A{a(0) - b(0), a(0) - c(0), ray.direction()(0),
                       a(1) - b(1), a(1) - c(1), ray.direction()(1),
                       a(2) - b(2), a(2) - c(2), ray.direction()(2)};

  // the three elements are beta, gamma, t respectively
  const auto result = solve(A, a - ray.source());

  const coordinate_type beta = result(0);
  const coordinate_type gamma = result(1);
  const coordinate_type t = result(2);

  if (gamma >= 0 && gamma <= 1 && beta >= 0 && beta <= (1 - gamma) &&
      t < upperbound && t >= lowerbound) {
    return std::pair{t, computeNormal(ray)};
  } else {
    return std::nullopt;
  }
}

Vector3 Triangle::computeNormal(Ray ray) const {
  Vector3 uNormal = normalize(crossProduct((a - b), (a - c)));
  if (scalarProduct(uNormal, ray.direction()) > 0) {
    return -uNormal;
  } else {
    return uNormal;
  }
}

BoundingBox Triangle::boundingbox() const {
  return {Point{min3(a(0), b(0), c(0)), min3(a(1), b(1), c(1)),
                min3(a(2), b(2), c(2))},
          Point{max3(a(0), b(0), c(0)), max3(a(1), b(1), c(1)),
                max3(a(2), b(2), c(2))}}; // doubt if this works...
}
} // namespace graphics