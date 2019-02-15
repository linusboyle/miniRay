#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "surface.hpp"

namespace graphics {
    class Sphere : public Surface {
        Point center_;
        coordinate_type radius_;

    public:
        Sphere(Point center, coordinate_type radius, RGBColor color): Surface(color), center_(center), radius_(radius) {}
        virtual intersect_type hit(const Ray& ray, coordinate_type upperbound) const;   
        virtual BoundingBox boundingbox() const;
        virtual ~Sphere() {}
        virtual Vector3 gradient(const Point& position) const;
    };
}
#endif /* ifndef SPHERE_HPP */
