#include "plane.hpp" 
#include "ray.hpp"
#include <cassert>

namespace graphics {
    Plane::Plane(Point p1, Point p2, Point p3, RGBColor color, bool reflective): Surface(color, reflective), a(std::move(p1)), b(std::move(p2)), c(std::move(p3)) {
        // we must have three different points
        assert(!(p1 == p2) && !(p2 == p3));
    }

    Vector3 Plane::normal() const {
        Vector3 u = b - a;
        Vector3 v = c - a;
        return u * v;
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
        if (scalarProduct(normal_, ray.direction()) == 0) { // parallel
            return {};
        }

        const auto result = solution(ray);
        const coordinate_type t = std::get<0>(result);

        if (t <= upperbound && t > lowerbound) {
            referrence_point = ray.source();
            return t;
        } else {
            return {};
        }
    }

    std::tuple<coordinate_type, coordinate_type, coordinate_type> Plane::solution(const Ray& ray) {

        // TODO:
        // change all these manual matrix computing
        // to Eigen .etc

        const coordinate_type a_ = a.getx() - b.getx();
        const coordinate_type b_ = a.gety() - b.gety();
        const coordinate_type c_ = a.getz() - b.getz();
        const coordinate_type d_ = a.getx() - c.getx();
        const coordinate_type e_ = a.gety() - c.gety();
        const coordinate_type f_ = a.getz() - c.getz();
        const coordinate_type g_ = ray.direction().getx();
        const coordinate_type h_ = ray.direction().gety();
        const coordinate_type i_ = ray.direction().getz();

        const coordinate_type j_ = a.getx() - ray.source().getx();
        const coordinate_type k_ = a.gety() - ray.source().gety();
        const coordinate_type l_ = a.getz() - ray.source().getz();

        const coordinate_type ei_hf = e_ * i_ - h_ * f_;
        const coordinate_type gf_di = g_ * f_ - d_ * i_;
        const coordinate_type dh_eg = d_ * h_ - e_ * g_;
        const coordinate_type ak_jb = a_ * k_ - j_ * b_;
        const coordinate_type jc_al = j_ * c_ - a_ * l_;
        const coordinate_type bl_kc = b_ * l_ - k_ * c_;

        const coordinate_type M = a_ * ei_hf + b_ * gf_di + c_ * dh_eg;
        coordinate_type t = (f_ * ak_jb + e_ * jc_al + d_ * bl_kc) / -M;
        coordinate_type beta = (j_ * ei_hf + k_ * gf_di + l_ * dh_eg) / M;
        coordinate_type gamma = (i_ * ak_jb + h_ * jc_al + g_ * bl_kc) / M;

        return std::make_tuple(t, beta, gamma);
    }
}
