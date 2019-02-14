#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "config.hpp"

namespace graphics {
    class basic_vector2 {
        coordinate_type x;
        coordinate_type y;

    public:
        basic_vector2(coordinate_type x, coordinate_type y): x(x), y(y) {}
        coordinate_type getx() const {return x;}
        coordinate_type gety() const {return y;}
        coordinate_type modulus() const;
    };

    class basic_vector3 {
        coordinate_type x;
        coordinate_type y;
        coordinate_type z;

    public:
        basic_vector3(coordinate_type x, coordinate_type y, coordinate_type z): x(x), y(y), z(z) {}
        coordinate_type getx() const {return x;}
        coordinate_type gety() const {return y;}
        coordinate_type getz() const {return z;}
        coordinate_type modulus() const;
    };

    basic_vector2 operator+(const basic_vector2& lhs, const basic_vector2& rhs);
    basic_vector2 operator-(const basic_vector2& lhs, const basic_vector2& rhs);
    basic_vector2 normalize(const basic_vector2& vec);

    basic_vector3 operator+(const basic_vector3& lhs, const basic_vector3& rhs);

    basic_vector3 operator-(const basic_vector3& operand);
    basic_vector3 operator-(const basic_vector3& lhs, const basic_vector3& rhs);

    basic_vector3 operator*(const basic_vector3& lhs, const basic_vector3& rhs);
    basic_vector3 operator*(coordinate_type lhs, const basic_vector3& rhs);

    basic_vector3 operator/(const basic_vector3& lhs, coordinate_type rhs);

    basic_vector3 normalize(const basic_vector3& vec);

    bool operator==(const basic_vector3& lhs, const basic_vector3& rhs);

    coordinate_type scalarProduct(const basic_vector2& lhs, const basic_vector2& rhs);
    coordinate_type scalarProduct(const basic_vector3& lhs, const basic_vector3& rhs);

    using Vector2 = basic_vector2;
    using Vector3 = basic_vector3;

    using Point = basic_vector3; // a 3d point can be seen as a vector
}

#endif /* ifndef VECTOR_HPP */
