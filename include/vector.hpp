#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"
#include <cmath>

namespace graphics {
    template <std::size_t Dimension>
    using basic_vector = Matrix<Dimension, 1>;

    using Vector2 = basic_vector<2>;
    using Vector3 = basic_vector<3>;

    template <std::size_t Dimension>
    auto scalarProduct(const basic_vector<Dimension>& lhs, const basic_vector<Dimension>& rhs) {
        coordinate_type retval = 0.0;
        for (std::size_t i = 0; i < Dimension; ++i) {
            retval += lhs(i, 0) * rhs(i, 0);
        }

        return retval;
    }

    Vector3 crossProduct(const Vector3& lhs, const Vector3& rhs);

    template <std::size_t Dimension>
    auto modulus(const basic_vector<Dimension>& v) {
        coordinate_type qsum = 0.0;
        for (std::size_t i = 0; i < Dimension; ++i) {
            qsum += v(i, 0) * v(i, 0);
        }

        return std::sqrt(qsum);
    }

    template <std::size_t Dimension>
    inline auto normalize(const basic_vector<Dimension>& v) {
        coordinate_type modulus = graphics::modulus(v);

        return v / modulus;
    }

    Vector3 solve(const Matrix<3, 3>& lhs, const Vector3& rhs);

    using Point = Vector3;
}
#endif /* ifndef VECTOR_HPP */
