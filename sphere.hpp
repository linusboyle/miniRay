#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "surface.hpp"

namespace graphics {
    class Sphere : public Surface {
        Point center_;
        coordinate_type radius_;

    public:
        Sphere(Point center, coordinate_type radius, RGBColor color): Surface(color), center_(center), radius_(radius) {}
        virtual intersect_type hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound) override;   
        virtual BoundingBox boundingbox() const override;
        virtual ~Sphere() {}
        virtual Vector3 gradient(const Point& position) const override;
    };
}
#endif /* ifndef SPHERE_HPP */
