#ifndef SURFACE_CPP
#define SURFACE_CPP

#include <optional>
#include "vector.hpp"

namespace graphics {
    class Ray;

    struct BoundingBox {
        Point first;
        Point second;
    };

    struct HitPoint {
        coordinate_type offset;
        Vector3 normal;
    };

    using intersect_type = std::optional<HitPoint>;

    class Surface {
    public:
        virtual ~Surface() = 0;
        virtual intersect_type hit(const Ray& ray, coordinate_type upperbound) const = 0;   
        virtual BoundingBox boundingbox() const = 0;
    };

    class Sphere : public Surface {
        Point center_;
        coordinate_type radius_;

        Vector3 gradient(const Ray& ray, coordinate_type position) const;
    public:
        Sphere(Point center, coordinate_type radius): center_(center), radius_(radius) {}
        virtual intersect_type hit(const Ray& ray, coordinate_type upperbound) const;   
        virtual BoundingBox boundingbox() const;
        virtual ~Sphere() {}
    };
}
#endif /* ifndef SURFACE_CPP */
