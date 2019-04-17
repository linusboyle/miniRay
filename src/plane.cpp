#include "plane.hpp"
#include "ray.hpp"

namespace graphics {
Plane::Plane(Point p, Vector3 normal, RGBColor color, bool reflective)
    : Surface(color, reflective), p_(std::move(p)), normal_(std::move(normal)) {}

Vector3 Plane::computeNormal(Ray ray) const {
  Vector3 uNormal = normalize(normal_);

  if (scalarProduct(uNormal, ray.direction()) > 0) {
    return -uNormal;
  } else {
    return uNormal;
  }
}

BoundingBox Plane::boundingbox() const { return {Point(), Point()}; }

intersect_type Plane::hit(const Ray &ray, coordinate_type lowerbound,
                          coordinate_type upperbound) {

  // parallel
  if (scalarProduct(normal_, ray.direction()) == 0.0) {
    return std::nullopt;
  }

  const coordinate_type t =
      (scalarProduct(normal_, p_) - scalarProduct(normal_, ray.source())) /
      scalarProduct(normal_, ray.direction());

  if (t <= upperbound && t > lowerbound) {
    return std::pair{t, computeNormal(ray)};
  } else {
    return std::nullopt;
  }
}

} // namespace graphics
