#include "surface.hpp" 
#include "ray.hpp"
#include <cmath>
#include <cassert>

// compute the discriminant of quadratic equation
// Ax^2 + Bx + C = 0
static inline graphics::coordinate_type discriminant(graphics::coordinate_type A, graphics::coordinate_type B, graphics::coordinate_type C) {
    return  B * B - 4 * A * C;
}

namespace graphics {
    Surface::~Surface() {}

    intersect_type Sphere::hit(const Ray& ray, coordinate_type upperbound) const {
        // coefficients
        coordinate_type A = scalarProduct(ray.direction(), ray.direction());
        coordinate_type B = 2 * scalarProduct(ray.direction(), ray.source() - center_);
        coordinate_type C = scalarProduct(ray.source() - center_, ray.source() - center_) - radius_ * radius_; 

        assert(A > 0);
        assert(C > 0);

        coordinate_type discriminant = ::discriminant(A, B, C);

        if (discriminant < 0) {
            return {};
        } else if (discriminant > 0) {
            // two roots
            coordinate_type root = std::sqrt(discriminant);
            coordinate_type x2 = (-B / 2 + root) / A;

            if (x2 < 0) { // intersect behind the camera
                return {};
            } else {
                coordinate_type x1 = (- B / 2 - root) / A;

                if (x1 <= upperbound) {
                    return HitPoint{x1, gradient(ray, x1)};
                } else {
                    return {};
                }
            }
        } else {
            coordinate_type x = (-B / 2) / A;
            if (x <= upperbound) {
                return HitPoint{x, gradient(ray, x)};
            } else {
                return {};
            }
        }
    }

    // the unit surface normal
    Vector3 Sphere::gradient(const Ray& ray, coordinate_type position) const {
        Point p = ray.source() + position * ray.direction();
        return (p - center_) / radius_;
    }

    BoundingBox Sphere::boundingbox() const {
        Point first = center_ - Point(radius_, radius_, radius_);
        Point second = center_ + Point(radius_, radius_, radius_);
        return {first, second};
    }
}