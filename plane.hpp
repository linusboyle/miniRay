#ifndef PLANE_HPP
#define PLANE_HPP

#include "surface.hpp"
#include <tuple>

namespace graphics {
    class Plane : public Surface {
        // three point determine a plane
        Point a;
        Point b;
        Point c;

        // this point is used to indicate which side of the plane
        // is 'positive'
        // this point should not be on the plane
        Point referrence_point;

        std::tuple<coordinate_type, coordinate_type, coordinate_type> solution(const Ray& ray);

        // helper function
        Vector3 normal() const;

        // triangle wrapper class
        friend class Triangle;
    public:

        // the order does not matter
        Plane(Point p1, Point p2, Point p3, RGBColor color);

        virtual intersect_type hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound) override;
        virtual BoundingBox boundingbox() const override;

        // NOTE: this function is meaningless for a plane
        virtual Vector3 gradient(const Point& position) const override;
        virtual ~Plane() {}

        // set ref point manually
        void setRefPoint(const Point& p) { referrence_point = p; }
    };
}

#endif /* ifndef PLANE_HPP */
