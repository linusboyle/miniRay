#include "catch.hpp"

#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"

using namespace graphics;

TEST_CASE ("ray and object intersection computed correctly", "[ray]") {
    Surface* sphere = new Sphere(Point{0.0, 0.0, 0.0}, 1.0, {26, 188, 156});
    Ray ray(Point{1.0, 1.0, 1.0}, Vector3{-1.0, -1.0, -1.0});
    auto result = sphere->hit(ray, 0, std::numeric_limits<coordinate_type>::max());
    REQUIRE(result);
    REQUIRE(result.value() - 0.42265 < std::numeric_limits<coordinate_type>::epsilon());
    REQUIRE(0.42265 - result.value() > std::numeric_limits<coordinate_type>::epsilon());
}

TEST_CASE("the ray tracing main function works correctly", "[ray]") {
    Image img(512, 512);
    img.fillcolor({255, 255, 255});

    Scene scene;
    scene.setAmbientIntensity(0.25);
    scene.addObject(new Sphere{Point{0.0, 0.0, 0.0}, 1.0, RGBColor{26, 188, 156}});
    scene.addObject(new Sphere{Point{-1.9, 1.1, 0.0}, 1, RGBColor{100, 20, 35}});
    scene.addObject(new Plane{Point{0.0, 0.0, -1.0}, Vector3{0.0, 0.0, 1.0}, RGBColor{70, 70, 70}, true});
    scene.addLightSource({Point{2.7, -0.3, 3.4}, 0.7});
    scene.addLightSource({Point{1.0, 4.3, 4.0}, 0.3});
    Camera camera(Point{5.0, 5.0, 5.0}, Vector3{-1.0, -1.0, -1.0}, 0.7, {-0.4, 0.4, 0.4, -0.4});
    scene.render(camera, img);

    img.show();
    img.writeout("rendered.png");
}