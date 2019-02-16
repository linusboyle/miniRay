#ifndef RAY_HPP
#define RAY_HPP

#include "vector.hpp"

namespace graphics {
    class Ray {
        Point source_;
        Vector3 direction_;

    public:
        Ray(const Point& source, const Vector3& direction): source_(source), direction_(direction) {}
        Point source() const { return source_; } 
        Vector3 direction() const { return direction_; }
    };
}

#endif /* ifndef RAY_HPP */
