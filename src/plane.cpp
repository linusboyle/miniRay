#include "plane.hpp" 
#include "ray.hpp"

namespace graphics {
    Plane::Plane(const Point& p1, const Point& p2, const Point& p3, RGBColor color, bool reflective): Surface(color, reflective), a(p1), b(p2), c(p3) {
        // we must have three different points
        if (p1 == p2 || p2 == p3 || p1 == p3) {
            throw std::invalid_argument("Plane must be constructed from three different points");
        }
    }

    Vector3 Plane::normal() const {
        Vector3 u = b - a;
        Vector3 v = c - a;
        return crossProduct(u, v);
    }

    // the gradient is a constant regardless of position on the plane
    Vector3 Plane::gradient(const Point&) const {
        Vector3 uNormal = normalize(normal());

        if (scalarProduct(uNormal, referrence_point - a) < 0) {
            return -uNormal;
        } else {
            return  uNormal;
        }
    }

    BoundingBox Plane::boundingbox() const {
        return {Point(), Point()};
    }

    intersect_type Plane::hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound) {

        const Vector3 normal_ = normal();
        if (scalarProduct(normal_, ray.direction()) == 0.0) { // parallel
            return {};
        }

        const auto result = solution(ray);
        const coordinate_type t = result.getElement(2, 0);

        if (t <= upperbound && t > lowerbound) {
            referrence_point = ray.source();
            return t;
        } else {
            return {};
        }
    }

    Vector3 Plane::solution(const Ray& ray) {

        const Matrix<3,3> A {
            a(0) - b(0), a(0) - c(0), ray.direction()(0),
            a(1) - b(1), a(1) - c(1), ray.direction()(1),
            a(2) - b(2), a(2) - c(2), ray.direction()(2)
        };

        const auto result = solve(A, a - ray.source());

        // the three elements are beta, gamma, t respectively
        return result;
    }
}
