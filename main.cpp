#include "scene.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "sphere.hpp"
#include "plane.hpp"

#include <cassert>
#include <iostream>

using namespace graphics;

int main() {

    // test vectors
    Vector3 a = {1, 0, 0};
    Vector3 b = {0, 1, 0};
    Vector3 c = {0, 0, 1};
    
    assert(-(-a) == a);
    assert((a + b + c) == Vector3(1, 1, 1));
    assert(scalarProduct(a, b) == 0);
    assert(a / 2 == Vector3(0.5, 0, 0));

    // right-hand frame
    assert(a * b == c);
    assert(a * c == -b);
    assert(b * c == a);
    assert(b * a == -c);
    assert(c * a == b);
    assert(c * b == -a);

    // cross
    assert(Vector3(2.4,0,0) * Vector3(0, 5.5, 0) == Vector3(0, 0, 13.2)); 

    // color / image
    Image img(Width(512), Height(512));
    img.fillcolor({0, 0, 0});

    // intersect
    Surface* sphere = new Sphere(Point{0, 0, 0}, 1.0, {26, 188, 156});
    Ray ray({1, 1, 1}, {-1, -1, -1});

    auto result = sphere->hit(ray, 0, std::numeric_limits<coordinate_type>::max());

    if (result) {
        coordinate_type point = result.value();
        Point p = ray.source() + point * ray.direction();
        std::cout << "hit at: " << p.getx() << ' ' << p.gety() << ' ' << p.getz() << ' ' << std::endl;
    } else {
        std::cout << "not hit" << std::endl;
    }
    
    // camera / scene
    Scene s;
    s.setAmbientIntensity(0.25);
    s.addObject(sphere);
    s.addObject(new Sphere({-1.9, 1.1, 0}, 1, {100, 20, 35}));
    s.addObject(new Plane{Point(1, 0, -1), Point(0, 1, -1), Point(0, -1, -1), {70, 70, 70}});
    s.addLightSource({Point(2.7, -0.3, 3.4), 0.7});
    s.addLightSource({Point(1.0, 4.3, 4), 0.3});
    Camera camera({5.0, 5.0, 5.0}, {-1, -1, -1}, 0.7, {-0.4, 0.4, 0.4, -0.4});
    s.render(camera, img);

    img.writeout("render.png");
    
    return 0;
}
