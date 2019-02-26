#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <ostream>
#include <iterator>

#include "config.hpp"
#include "meta.hpp"

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

        template <typename Iterator, std::enable_if_t<meta::is_forward_iterator_v<Iterator>, bool> = true>
        explicit base_matrix(Iterator begin, Iterator end) {
            std::size_t i = 0;
            while(begin != end) {
                if (i >= ROWS * COLUMNS) {
                    throw std::logic_error("number of matrix elements is wrong!");
                }
                matrix_[i++] = *begin;
                begin++;
            }
        }

        template <typename... EList, std::enable_if_t<meta::nonarrow_convertible<T, EList...>::value, bool> = true>
        explicit base_matrix(EList&&... es): matrix_{std::forward<EList>(es)...} {
            static_assert(sizeof...(es) == ROWS * COLUMNS, "elements number does not match the size of the matrix!");
        }

        template <typename F>
        void for_each(F&& f) {
            for (std::size_t i = 0; i < ROWS; ++i) {
                for (std::size_t j = 0; j < COLUMNS; ++j) {
                    matrix_[cConvert(i, j)] = f(i, j);
                }
            }
        }

        auto transpose() const {
            base_matrix<ROWS, COLUMNS, T> trans;
            trans.for_each([this](auto i, auto j) {
                    return this->matrix_[this->cConvert(j, i)];
                    });

            return trans;
        }

        T& operator() (std::size_t row, std::size_t column) {
            return matrix_[cConvert(row, column)];
        }

        const T& operator() (std::size_t row, std::size_t column) const {
            return matrix_[cConvert(row, column)];
        }

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
            retval.for_each([&lhs, denominator](auto i, auto j){
                        return lhs(i, j) / denominator;
                    });
            return retval;
        }

        friend auto operator*(T e, const base_matrix<ROWS, COLUMNS, T>& rhs) {
            base_matrix<ROWS, COLUMNS, T> retval;
            retval.for_each([&rhs, e](auto i, auto j) {
                        return rhs(i, j) * e;
                    });

            return retval;
        }

        friend auto operator*(const base_matrix<ROWS, COLUMNS, T>& lhs, T e) {
            base_matrix<ROWS, COLUMNS, T> retval;
            retval.for_each([&lhs, e](auto i, auto j) {
                        return lhs(i, j) * e;
                    });

            return retval;
        }

    };

    template <std::size_t N, std::size_t M, std::size_t P, typename T>
    auto operator*(const base_matrix<N, M, T>& lhs, const base_matrix<M, P, T>& rhs) {
        base_matrix<N, P, T> retval;
        retval.for_each([&lhs, &rhs](auto i, auto j) {
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
        retval.for_each([&lhs, &rhs](auto i, auto j) {
                    return lhs(i, j) + rhs(i, j);
                });

        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator-(const base_matrix<N, M, T>& lhs, const base_matrix<N, M, T> &rhs) {
        base_matrix<N, M, T> retval;
        retval.for_each([&lhs, &rhs](auto i, auto j) {
                    return lhs(i, j) - rhs(i, j);
                });
        return retval;
    }

    template <std::size_t N, std::size_t M, typename T>
    auto operator-(const base_matrix<N, M, T>& v) {
        base_matrix<N, M, T> retval;
        retval.for_each([&v](auto i, auto j) {
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

    template <std::size_t N, std::size_t M>
    using MatrixD = base_matrix<N, M, coordinate_type>;
}
#endif /* ifndef MATRIX_HPP */
