#include "catch.hpp"
#include "vector.hpp"

using namespace graphics;

TEST_CASE ("vectors can be calculated correctly", "[vector]") {
    Vector3 a {2.4, 0.0, 0.0};
    Vector3 b {0.0, 5.5, 0.0};
    Vector3 c {0.0, 0.0, 13.2};

    REQUIRE (a(0) == 2.4);
    REQUIRE (b(1) == 5.5);
    REQUIRE (c(2) == 13.2);

    SECTION("invert a vector correctly") {
        REQUIRE (-(-a) == a);
    }
    SECTION("vectors add correctly") {
        REQUIRE ((a + b + c) == Vector3{2.4, 5.5, 13.2});
    }
    SECTION("scalarProduct of vertical vectors is 0") {
        REQUIRE (scalarProduct(a, b) == 0);
    }
    SECTION("crossProduct of vectors computed correctly") {
        REQUIRE (crossProduct(a, b) == c);
    }
}
