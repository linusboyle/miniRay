#include "camera.hpp"
#include "image.hpp"
#include "plane.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

using namespace graphics;

int main () {
    Image img(1024, 768);
    img.fillcolor({0, 0, 0});

    Scene scene;
    // scene.setAmbientIntensity({0.25, 0.25, 0.25});
    // left
    scene.addObject(new Plane{Point{0.0, 0.0, 0.0}, Vector3{0.0, 1.0, 0.0},
            RGBColor{191, 64, 64}});
    // right
    scene.addObject(new Plane{Point{0.0, 120.0, 0.0}, Vector3{0.0, -1.0, 0.0},
            RGBColor{64, 64, 191}});
    // front
    scene.addObject(new Plane{Point{170.0, 0.0, 0.0}, Vector3{-1.0, 0.0, 0.0},
            RGBColor{0, 0, 0}});
    // back
    scene.addObject(new Plane{Point{0.0, 0.0, 0.0}, Vector3{1.0, 0.0, 0.0},
            RGBColor{191, 191, 191}});
    // bottom
    scene.addObject(new Plane{Point{0.0, 0.0, 0.0}, Vector3{0.0, 0.0, 1.0},
            RGBColor{191, 191, 191}});
    // top
    scene.addObject(new Plane{Point{0.0, 0.0, 106.0}, Vector3{0.0, 0.0, -1.0},
            RGBColor{191, 191, 191}});
    // sphere
    //scene.addObject(new Sphere{Point{26.3, 45.5, 16.5}, 16.5, RGBColor{0.3, 0.3, 0.3}});

    // light
    scene.addObject(new Sphere{Point{41.0, 60.0, 1306.0 - .04}, 1200.0, RGBColor{0, 0, 0}, RGBColor{11.3, 11.3, 11.3}});
    //scene.addObject(new Triangle{Point{40.0, 60.0, 100.0 - .12}, Point{40.0, 40.0, 100.0 - .12}, Point{23.0, 50.0, 100.0 - .12}, RGBColor{0, 0, 0}, RGBColor{0.7, 0.7, 0.7}});

    Camera camera(Point{80.0, 60.0, 59.2}, Vector3{-1.0, 0.0, -0.027}, 2.4, 4);
    scene.render(camera, img, 1);

    img.writeout("cornell.png");
    img.show();
}
