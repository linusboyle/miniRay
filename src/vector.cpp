#include <cmath>
#include "vector.hpp"

namespace graphics {
    coordinate_type basic_vector2::modulus() const {
        return std::sqrt(x * x + y * y);
    }

    basic_vector2 operator+(const basic_vector2& lhs, const basic_vector2& rhs) {
        return {lhs.getx() + rhs.getx(), lhs.gety() + rhs.gety()};
    }

    basic_vector2 operator-(const basic_vector2& lhs, const basic_vector2& rhs) {
        return {lhs.getx() - rhs.getx(), lhs.gety() - rhs.gety()};
    }

    coordinate_type scalarProduct(const basic_vector2& lhs, const basic_vector2& rhs) { 
        return (lhs.getx() * rhs.getx() + lhs.gety() * rhs.gety());
    }

    basic_vector2 normalize(const basic_vector2& vec) {
        coordinate_type modulus = vec.modulus();

        return {vec.getx() / modulus, vec.gety() / modulus};
    }

    basic_vector3 operator+(const basic_vector3& lhs, const basic_vector3& rhs) {
        return {lhs.getx() + rhs.getx(), lhs.gety() + rhs.gety(), lhs.getz() + rhs.getz()};
    }

    basic_vector3 operator-(const basic_vector3& lhs, const basic_vector3& rhs) {
        return {lhs.getx() - rhs.getx(), lhs.gety() - rhs.gety(), lhs.getz() - rhs.getz()};
    }

    coordinate_type scalarProduct(const basic_vector3& lhs, const basic_vector3& rhs) { 
        return (lhs.getx() * rhs.getx() + lhs.gety() * rhs.gety() + lhs.getz() * rhs.getz());
    }

    coordinate_type basic_vector3::modulus() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    basic_vector3 normalize(const basic_vector3& vec) {
        coordinate_type modulus = vec.modulus();
        return {vec.getx() / modulus, vec.gety() / modulus, vec.getz() / modulus};
    }

    // 3D vector only, cross/vector product
    basic_vector3 operator*(const basic_vector3& lhs, const basic_vector3& rhs) {
        return {lhs.gety() * rhs.getz() - lhs.getz() * rhs.gety(), lhs.getz() * rhs.getx() - lhs.getx() * rhs.getz(), lhs.getx() * rhs.gety() - lhs.gety() * rhs.getx()};
    }


    basic_vector3 operator*(coordinate_type lhs, const basic_vector3& rhs) {
        return {lhs * rhs.getx(), lhs * rhs.gety(), lhs * rhs.getz()};
    }

    basic_vector3 operator-(const basic_vector3& operand) {
        return {-operand.getx(), -operand.gety(), -operand.getz()};
    }

    basic_vector3 operator/(const basic_vector3& lhs, coordinate_type rhs) {
        return {lhs.getx() / rhs, lhs.gety() / rhs, lhs.getz() / rhs};
    }

    bool operator==(const basic_vector3& lhs, const basic_vector3& rhs) {
        return (lhs.getx() == rhs.getx() && lhs.gety() == rhs.gety() && lhs.getz() == rhs.getz());
    }
}
