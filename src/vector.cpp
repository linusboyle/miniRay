#include "vector.hpp"

namespace graphics {
    Vector3 crossProduct(const Vector3& lhs, const Vector3& rhs) {
        return Vector3({lhs(1,0) * rhs(2,0) - lhs(2,0) * rhs(1,0), lhs(2,0) * rhs(0,0) - lhs(0,0) * rhs(2,0), lhs(0,0) * rhs(1,0) - lhs(1,0) * rhs(0,0)});
    }
}
