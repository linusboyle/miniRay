#include "surface.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "image.hpp"

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
    Surface* surface = new Sphere(Point{0, 0, 0}, 1.0, {92, 113, 68});
    Ray ray({1, 1, 1}, {-1, -1, -1});

    auto result = surface->hit(ray, std::numeric_limits<coordinate_type>::max());

    if (result) {
        HitPoint point = result.value();
        Point p = ray.source() + point.offset * ray.direction();
        std::cout << "hit at: " << p.getx() << ' ' << p.gety() << ' ' << p.getz() << ' ' << std::endl;
    } else {
        std::cout << "not hit" << std::endl;
    }
    
    // camera / scene
    Scene s;
    s.addObject(surface);
    s.addLightSource({Point(2.1, 0.2, 3), 0.7});
    Camera camera({5.0, 5.0, 5.0}, {-1, -1, -1}, 1.2, {-2, 2, 2, -2});
    s.render(camera, img);

    img.writeout("Sphere.png");
    
    return 0;
}
