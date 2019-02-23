#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstring>
#include <type_traits>
#include <ostream>

#include "config.hpp"

namespace graphics {
    template <std::size_t ROWS, std::size_t COLUMNS, typename T>
    class base_matrix {

        static_assert(COLUMNS > 0);
        static_assert(ROWS > 0);
        static_assert(std::is_arithmetic<T>::value);

        T matrix_[ROWS * COLUMNS];

        static constexpr std::size_t cConvert(std::size_t row, std::size_t column)  {
            return row * COLUMNS + column;
        }
    public:
        base_matrix() {}
        explicit base_matrix(const T source[ROWS * COLUMNS]) { // unsafe
            std::memcpy(matrix_, source, sizeof(T) * ROWS * COLUMNS);
        }

        // TODO:
        // a more generic constructor using variadic template

        base_matrix(std::initializer_list<T> l) {
            if (l.size() != ROWS * COLUMNS) {
                throw std::logic_error("number of elements is incorrect!");
            }
            std::size_t i = 0; 
            for (const auto& e : l) {
                matrix_[i++] = e;
            }
        }

        T& operator() (std::size_t row, std::size_t column) {
            return matrix_[cConvert(row, column)];
        };

        const T& operator() (std::size_t row, std::size_t column) const {
            return matrix_[cConvert(row, column)];
        };

        bool operator==(const base_matrix<ROWS, COLUMNS, T>& another) const {
            for (std::size_t i = 0; i < ROWS; ++i) {
                for (std::size_t j = 0; j < COLUMNS; ++j) {
                    if (matrix_[cConvert(i, j)] != another(i, j))
                        return false;
                }
            }
            return true;
        }

        friend auto operator/(const base_matrix<ROWS, COLUMNS, T>& lhs, T denominator) {
            base_matrix<ROWS, COLUMNS, T> retval;
            for (std::size_t i = 0; i < ROWS; ++i) {
                for (std::size_t j = 0; j < COLUMNS; ++j) {
                    retval(i, j) = lhs(i, j) / denominator;
                }
            }
            return retval;
        }

        friend auto operator*(T e, const base_matrix<ROWS, COLUMNS, T>& rhs) {
            base_matrix<ROWS, COLUMNS, T> retval;
            for (std::size_t i = 0; i < ROWS; ++i) {
                for (std::size_t j = 0; j < COLUMNS; ++j) {
                    retval(i, j) = rhs(i, j) * e;
                }
            }

            return retval;
        }

        friend auto operator*(const base_matrix<ROWS, COLUMNS, T>& lhs, T e) {
            base_matrix<ROWS, COLUMNS, T> retval;
            for (std::size_t i = 0; i < ROWS; ++i) {
                for (std::size_t j = 0; j < COLUMNS; ++j) {
                    retval(i, j) = lhs(i, j) * e;
                }
            }

            return retval;
        }

    };

    template <std::size_t N, std::size_t M, std::size_t P, typename T>
    auto operator*(const base_matrix<N, M, T>& lhs, const base_matrix<M, P, T>& rhs) {
        base_matrix<N, P, T> retval;
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < P; ++j) {
                retval(i, j) = 0;
                for (std::size_t k = 0; k < M; ++k) {
                    retval(i, j) += lhs(i, k) * rhs(k, j);
                }
            }
        }

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator+(const base_matrix<N, M, T>& lhs, const base_matrix<N, M, T> &rhs) {
        base_matrix<N, M, T> retval;
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                retval(i, j) = lhs(i, j) + rhs(i, j);
            }
        }

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator-(const base_matrix<N, M, T>& lhs, const base_matrix<N, M, T> &rhs) {
        base_matrix<N, M, T> retval;
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                retval(i, j) = lhs(i, j) - rhs(i, j);
            }
        }

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator-(const base_matrix<N, M, T>& v) {
        base_matrix<N, M, T> retval;
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                retval(i, j) = -v(i, j);
            }
        }

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

    template <std::size_t N, std::size_t M>
    using MatrixD = base_matrix<N, M, coordinate_type>;
}
#endif /* ifndef MATRIX_HPP */
