#include "plane.hpp" 
#include "ray.hpp"

namespace graphics {
    Plane::Plane(const Point& p1, const Point& p2, const Point& p3, RGBColor color, bool reflective): Surface(color, reflective), a(p1), b(p2), c(p3) {
        // we must have three different points
        if (p1 == p2 || p2 == p3 || p1 == p3) {
            throw std::logic_error("Plane must be constructed from three different points");
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

        Matrix<3,3> m1 {
            get<0>(a) - get<0>(ray.source()), get<0>(a) - get<0>(c), get<0>(ray.direction()),
            get<1>(a) - get<1>(ray.source()), get<1>(a) - get<1>(c), get<1>(ray.direction()),
            get<2>(a) - get<2>(ray.source()), get<2>(a) - get<2>(c), get<2>(ray.direction())
        };

        Matrix<3,3> m2 {
            get<0>(a) - get<0>(b), get<0>(a) - get<0>(ray.source()), get<0>(ray.direction()),
            get<1>(a) - get<1>(b), get<1>(a) - get<1>(ray.source()), get<1>(ray.direction()),
            get<2>(a) - get<2>(b), get<2>(a) - get<2>(ray.source()), get<2>(ray.direction())
        };

        Matrix<3,3> m3 {
            get<0>(a) - get<0>(b), get<0>(a) - get<0>(c), get<0>(a)-get<0>(ray.source()),
            get<1>(a) - get<1>(b), get<1>(a) - get<1>(c), get<1>(a)-get<1>(ray.source()),
            get<2>(a) - get<2>(b), get<2>(a) - get<2>(c), get<2>(a)-get<2>(ray.source())
        };

        Matrix<3,3> A {
            get<0>(a) - get<0>(b), get<0>(a) - get<0>(c), get<0>(a)-get<0>(ray.direction()),
            get<1>(a) - get<1>(b), get<1>(a) - get<1>(c), get<1>(a)-get<1>(ray.direction()),
            get<2>(a) - get<2>(b), get<2>(a) - get<2>(c), get<2>(a)-get<2>(ray.direction())
        };

        coordinate_type dA = determinant(A);
        //const coordinate_type a_ = get<0>(a) - get<0>(b);
        //const coordinate_type b_ = get<1>(a) - get<1>(b);
        //const coordinate_type c_ = get<2>(a) - get<2>(b);
        //const coordinate_type d_ = get<0>(a) - get<0>(c);
        //const coordinate_type e_ = get<1>(a) - get<1>(c);
        //const coordinate_type f_ = get<2>(a) - get<2>(c);

        //const coordinate_type g_ = get<0>(ray.direction());
        //const coordinate_type h_ = get<1>(ray.direction());
        //const coordinate_type i_ = get<2>(ray.direction());

        //const coordinate_type j_ = get<0>(a) - get<0>(ray.source());
        //const coordinate_type k_ = get<1>(a) - get<1>(ray.source());
        //const coordinate_type l_ = get<2>(a) - get<2>(ray.source());

        //const coordinate_type ei_hf = e_ * i_ - h_ * f_;
        //const coordinate_type gf_di = g_ * f_ - d_ * i_;
        //const coordinate_type dh_eg = d_ * h_ - e_ * g_;
        //const coordinate_type ak_jb = a_ * k_ - j_ * b_;
        //const coordinate_type jc_al = j_ * c_ - a_ * l_;
        //const coordinate_type bl_kc = b_ * l_ - k_ * c_;
        //const coordinate_type M = a_ * ei_hf + b_ * gf_di + c_ * dh_eg;

        //coordinate_type t = (f_ * ak_jb + e_ * jc_al + d_ * bl_kc) / -M;
        //coordinate_type beta = (j_ * ei_hf + k_ * gf_di + l_ * dh_eg) / M;
        //coordinate_type gamma = (i_ * ak_jb + h_ * jc_al + g_ * bl_kc) / M;


        const coordinate_type t = determinant(m1) / dA;
        const coordinate_type beta = determinant(m2) / dA;
        const coordinate_type gamma = determinant(m3) / dA;

        return std::make_tuple(t, beta, gamma);
    }
}
