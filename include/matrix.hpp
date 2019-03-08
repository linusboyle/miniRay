#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "base_matrix.hpp"
#include "config.hpp"

#include <ostream>

namespace graphics {

    template <std::size_t N, std::size_t M, typename T>
    bool operator==(const base_matrix<N, M, T>& lhs, const base_matrix<N, M, T>& rhs) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                if (lhs.getElement(i, j) != rhs.getElement(i, j))
                    return false;
        }
        return true;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator/(const base_matrix<N, M, T>& lhs, T denominator) {
        base_matrix<N, M, T> retval;
        retval.assign([&lhs, denominator](auto i, auto j) {
                    return lhs(i, j) / denominator;
                });

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator*(T e, const base_matrix<N, M, T>& rhs) {
        base_matrix<N, M, T> retval;
        retval.assign([&rhs, e](auto i, auto j) {
                    return rhs(i, j) * e;
                });

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator*(const base_matrix<N, M, T>& lhs, T e) {
        base_matrix<N, M, T> retval;
        retval.assign([&lhs, e](auto i, auto j) {
                    return lhs(i, j) * e;
                });

        return retval;
    }

    template <std::size_t N, std::size_t M, std::size_t P, typename T>
    auto operator*(const base_matrix<N, M, T>& lhs, const base_matrix<M, P, T>& rhs) {
        base_matrix<N, P, T> retval;
        retval.assign([&lhs, &rhs](auto i, auto j) {
                    T a;
                    for (std::size_t k = 0; k < M; ++k) {
                        a += lhs(i, k) * rhs(k, j);
                    }

                    return a;
                });

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator+(const base_matrix<N, M, T>& lhs, const base_matrix<N, M, T> &rhs) {
        base_matrix<N, M, T> retval;
        retval.assign([&lhs, &rhs](auto i, auto j) {
                    return lhs(i, j) + rhs(i, j);
                });

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator-(const base_matrix<N, M, T>& lhs, const base_matrix<N, M, T> &rhs) {
        base_matrix<N, M, T> retval;
        retval.assign([&lhs, &rhs](auto i, auto j) {
                    return lhs(i, j) - rhs(i, j);
                });
        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator-(const base_matrix<N, M, T>& v) {
        base_matrix<N, M, T> retval;
        retval.assign([&v](auto i, auto j) {
                    return -v(i, j);
                });
        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    std::ostream& operator<< (std::ostream& out, const base_matrix<N, M, T>& matrix) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                out << matrix(i, j) << ' ';
            }
            out << std::endl;
        }

        return out;
    }

    template <std::size_t ROWS, std::size_t COLUMNS, typename T>
    T determinant(const base_matrix<ROWS, COLUMNS, T>& matrix) { 
        static_assert(ROWS == COLUMNS, "only square matrix has determinant");
        static_assert(ROWS <= 3, "only 3d matrix has determinant implemented");

        if constexpr (ROWS == 1) {
            return matrix.getElement(0, 0);
        } else if constexpr (ROWS == 2) {
            return matrix.getElement(0, 0) * matrix.getElement(1, 1) - matrix.getElement(0, 1) * matrix.getElement(1, 0);
        } else {
            return    matrix.getElement(0, 0) * matrix.getElement(1, 1) * matrix.getElement(2, 2) 
                    - matrix.getElement(0, 0) * matrix.getElement(2, 1) * matrix.getElement(1, 2) 
                    - matrix.getElement(0, 1) * matrix.getElement(1, 0) * matrix.getElement(2, 2)
                    + matrix.getElement(0, 1) * matrix.getElement(2, 0) * matrix.getElement(1, 2) 
                    + matrix.getElement(0, 2) * matrix.getElement(1, 0) * matrix.getElement(2, 1) 
                    - matrix.getElement(0, 2) * matrix.getElement(2, 0) * matrix.getElement(1, 1);
        }
    }

    template <std::size_t ROWS, std::size_t COLUMNS, typename T>
    auto transpose(const base_matrix<ROWS, COLUMNS, T>& matrix) {
        decltype(matrix) retval;
        retval.assign([&matrix](auto i, auto j) {
                    return matrix.getElement(j, i);
                });

        return retval;
    }

    //template <std::size_t ROWS, std::size_t COLUMNS, typename T>
    //auto inverse(const base_matrix<ROWS, COLUMNS, T>& matrix) {

    //}

    template <std::size_t N, std::size_t M>
    using Matrix = base_matrix<N, M, coordinate_type>;
}

#endif /* ifndef MATRIX_HPP */
