#include "catch.hpp"

#include "image.hpp"
#include "color.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"

using namespace graphics;

//#include "cereal/archives/json.hpp"
//#include "cereal/types/vector.hpp"

TEST_CASE ("ray and object intersection computed correctly", "[ray]") {
    //Image img {512, 512};
    //img.fillcolor({0, 0, 0});

    Surface* sphere = new Sphere(Point{0.0, 0.0, 0.0}, 1.0, {26, 188, 156});
    Ray ray(Point{1.0, 1.0, 1.0}, Vector3{-1.0, -1.0, -1.0});
    auto result = sphere->hit(ray, 0, std::numeric_limits<coordinate_type>::max());
    REQUIRE(result);
}
