#include "catch.hpp"

#include "matrix.hpp"

using namespace graphics;

TEST_CASE("1d matrix computation is correct", "[matrix]") {
    Matrix<1, 1> m{12.0};

    REQUIRE(m.getElement(0, 0) == 12.0);
    REQUIRE(m(0) == 12.0);
    REQUIRE(determinant(m) == 12.0);

    SECTION("1d matrix multiplication is correct") {
        Matrix<1, 1> n{5.0};

        auto p = m * n;
        REQUIRE(std::is_same_v<decltype(p), Matrix<1, 1>>);
        REQUIRE(p.getElement(0, 0) == 60.0);
    }
}

TEST_CASE("2d matrix computation is correct", "[matrix]") {
    Matrix<2, 2> m {1.0, 0.0,
                    0.0, 1.0};
    REQUIRE(m(0) == 1.0);
    REQUIRE(m(1) == 0.0);
    REQUIRE(determinant(m) == 1.0);

    m(0, 1) = 1.0;
    m(1, 0) = 1.0;

    REQUIRE(m(1) == 1.0);
    REQUIRE(determinant(m) == 0.0);

    SECTION("2d matrix multiplication is correct") {
        decltype(m) n {2.0, 3.0,
                       4.0, 0.0};

        auto p = m * n;
        REQUIRE(std::is_same_v<decltype(p), Matrix<2, 2>>);
        REQUIRE(p(0) == 6.0);
        REQUIRE(determinant(p) == 0.0);
    }
}

TEST_CASE("3d matrix computation is correct", "[matrix]") {
    Matrix<3, 3> m {1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0}; // intensity

    REQUIRE(determinant(m) == 1.0);

    decltype(m) n {100.0, 200.0, 300.0,
                   1000.0, 123.0, 1234.0,
                   12.0, 4.0, 23.0};

    auto p = m * n;
    REQUIRE(std::is_same_v<decltype(p), decltype(m)>);
    REQUIRE(p == n);
}