#ifndef SURFACE_CPP
#define SURFACE_CPP

#include "vector.hpp"
#include "color.hpp"

#include <optional>

namespace graphics {

    class Ray;

    struct BoundingBox {
        Point first;
        Point second;
    };

    using intersect_type = std::optional<coordinate_type>;

    class Surface {
        RGBColor color_;
        bool reflective;
    public:
        Surface(const RGBColor& color, bool reflective = false): color_(color), reflective(reflective) {}

        RGBColor color() const { return color_; }
        bool isReflective() const { return reflective; }

        virtual ~Surface() = 0;
        virtual intersect_type hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound) = 0;   
        virtual BoundingBox boundingbox() const = 0;
        virtual Vector3 gradient(const Point& position) const = 0;
    };
}
#endif /* ifndef SURFACE_CPP */
