#ifndef BASE_MATRIX_HPP
#define BASE_MATRIX_HPP

#include "meta.hpp"

namespace graphics {
    template <std::size_t ROWS, std::size_t COLUMNS, typename T>
    class base_matrix {

    public:
        static_assert(COLUMNS > 0);
        static_assert(ROWS > 0);
        static_assert(std::is_arithmetic<T>::value);

        static constexpr std::size_t size = ROWS * COLUMNS;
        static constexpr std::size_t rlength = ROWS;
        static constexpr std::size_t clength = COLUMNS;

    private:
        T matrix_[size];

    public:
        base_matrix() {}

        template <typename Iterator, std::enable_if_t<meta::is_forward_iterator_v<Iterator>, bool> = true>
        explicit base_matrix(Iterator begin, Iterator end) { // runtime
            // TODO: need some refactor
            std::size_t i = 0;
            while (begin != end) {
                if (i >= size) {
                    throw std::length_error("number of matrix elements is wrong!");
                }
                matrix_[i++] = *begin;
                begin++;
            }
        }

        template <typename... EList, std::enable_if_t<meta::nonarrow_convertible<T, EList...>::value, bool> = true>
        explicit base_matrix(EList&&... es): matrix_{std::forward<EList>(es)...} {
            static_assert(sizeof...(es) == size, "elements number does not match the size of the matrix!");
        }

        T& getElement(std::size_t row, std::size_t column) {
            return matrix_[ row * COLUMNS + column ];
        }

        const T& getElement(std::size_t row, std::size_t column) const {
            return matrix_[ row * COLUMNS + column ];
        }

        T& operator() (std::size_t row, std::size_t column = 0ul) {
            return getElement(row, column);
        }

        const T& operator() (std::size_t row, std::size_t column = 0ul) const {
            return getElement(row, column);
        }

        template <typename F>
        void assign(F&& f) {
            for (std::size_t i = 0; i < ROWS; ++i) {
                for (std::size_t j = 0; j < COLUMNS; ++j) {
                    getElement(i, j) = f(i, j);
                }
            }
        }
    };
}

#endif /* ifndef BASE_MATRIX_HPP */
