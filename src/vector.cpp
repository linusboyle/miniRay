#include "vector.hpp"

namespace graphics {
    Vector3 crossProduct(const Vector3& lhs, const Vector3& rhs) {
        return Vector3 {lhs(1,0) * rhs(2,0) - lhs(2,0) * rhs(1,0), lhs(2,0) * rhs(0,0) - lhs(0,0) * rhs(2,0), lhs(0,0) * rhs(1,0) - lhs(1,0) * rhs(0,0)};
    }

    Vector3 solve(const Matrix<3, 3>& lhs, const Vector3& rhs) {
        // using clamer's rule for this
        const coordinate_type dA = determinant(lhs);

        const coordinate_type a = lhs(0, 0);
        const coordinate_type b = lhs(1, 0);
        const coordinate_type c = lhs(2, 0);

        const coordinate_type d = lhs(0, 1);
        const coordinate_type e = lhs(1, 1);
        const coordinate_type f = lhs(2, 1);

        const coordinate_type g = lhs(0, 2);
        const coordinate_type h = lhs(1, 2);
        const coordinate_type i = lhs(2, 2);

        const coordinate_type j = rhs(0);
        const coordinate_type k = rhs(1);
        const coordinate_type l = rhs(2);

        const Matrix<3, 3> m1 {
            j, d, g,
            k, e, h,
            l, f, i
        };

        const Matrix<3, 3> m3 {
            a, d, j,
            b, e, k,
            c, f, l
        };

        const Matrix<3, 3> m2 {
            a, j, g,
            b, k, h,
            c, l, i
        };

        const coordinate_type r1 = determinant(m1) / dA;
        const coordinate_type r2 = determinant(m2) / dA;
        const coordinate_type r3 = determinant(m3) / dA;

        return Vector3{r1, r2, r3};
    }
};
