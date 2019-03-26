#ifndef PLANE_HPP
#define PLANE_HPP

#include "surface.hpp"
#include "vector.hpp"

namespace graphics {
    class Plane : public Surface {
        // a point and a normal vector define an (infinite) plane
        const Point p_;
        const Vector3 normal_;

        // a coefficient determined by p_ and normal_,
        // as the equation of the plane holds: p_ * normal_ + D = 0
        // It's provided to simplify computation
        const coordinate_type D;

        // this point is used to indicate which side of the plane
        // is 'positive'. Though there should be a better way to 
        // to this, right now it works fine.
        // NOTE: this point shouldn't be on the plane
        Point referrence_point;
    public:
        Plane(Point p, Vector3 normal, RGBColor color, bool reflective = false);

        virtual intersect_type hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound) override;

        // TODO
        // this function is meaningless for a plane
        // There should be a method to get around this
        virtual BoundingBox boundingbox() const override;

        // the gradient is a constant regardless of position on the plane
        virtual Vector3 gradient(const Point& position) const override;
        virtual ~Plane() override {}

        // set ref point manually
        void setRefPoint(const Point& p) { referrence_point = p; }
    };
}

#endif /* ifndef PLANE_HPP */
