#include "plane.hpp" 
#include "ray.hpp"

namespace graphics {
    Plane::Plane(Point p, Vector3 normal, RGBColor color, bool reflective)
        : Surface(color, reflective)
        , p_(std::move(p))
        , normal_(std::move(normal))
        , D(-scalarProduct(p_, normal_)) 
    {}

    Vector3 Plane::gradient(const Point&) const {
        Vector3 uNormal = normalize(normal_);

        if (scalarProduct(uNormal, referrence_point - p_) < 0) {
            return -uNormal;
        } else {
            return  uNormal;
        }
    }

    BoundingBox Plane::boundingbox() const {
        return {Point(), Point()};
    }

    intersect_type Plane::hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound) {
        if (scalarProduct(normal_, ray.direction()) == 0.0) { // parallel
            return {};
        }

        const coordinate_type t = 
            - ( D + scalarProduct(normal_, ray.source()) ) 
            / scalarProduct(normal_, ray.direction());

        if (t <= upperbound && t > lowerbound) {
            referrence_point = ray.source();
            return t;
        } else {
            return std::nullopt;
        }
    }

    //Vector3 Plane::solution(const Ray& ray) {

        //const Matrix<3,3> A {
            //a(0) - b(0), a(0) - c(0), ray.direction()(0),
            //a(1) - b(1), a(1) - c(1), ray.direction()(1),
            //a(2) - b(2), a(2) - c(2), ray.direction()(2)
        //};

        //const auto result = solve(A, a - ray.source());

        //// the three elements are beta, gamma, t respectively
        //return result;
    //}
}
