#include "scene.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "surface.hpp"

#include <algorithm>
#include <limits>

namespace graphics {
    void Scene::render(const Camera& camera, Image& img) const {
        auto plane = camera.imagePlane();
        const coordinate_type pWidth = plane.right_bound - plane.left_bound;
        const coordinate_type pHeight = plane.top_bound - plane.bottom_bound;

        const coordinate_type uStep = pWidth / img.width();
        const coordinate_type vStep = pHeight / img.height();

        for (unsigned int i = 0; i < img.width(); ++i) {
            coordinate_type u = plane.left_bound + (i + 0.5) * uStep;
            for (unsigned int j = 0; j < img.height(); ++j) {
                coordinate_type v = plane.top_bound - (j + 0.5) * vStep;
                Ray ray = camera.genRay(u, v);
                
                Surface* hitObj = nullptr;
                coordinate_type hitPosition = std::numeric_limits<coordinate_type>::max();

                std::for_each(std::begin(objects), std::end(objects), 
                        [&ray, &hitPosition, &hitObj](Surface* obj) { 
                            auto result = obj->hit(ray, hitPosition);
                            if (result) {
                                hitPosition = result.value();
                                hitObj = obj;
                            }
                        });

                // suppose the image has been filled with background color before render 
                // process, so that no trouble for that here.
                
                if (hitObj) {
                    // begin shading
                    Point p = ray.source() + hitPosition * ray.direction();
                    Vector3 normal = hitObj->gradient(p);

                    // simple lambertian shading
                    for (auto light : lights) {
                        RGBColor pColor = std::max(0.0, scalarProduct(normal,normalize(light.position - p))) * light.intensity * hitObj->color();
                        img.setpixel(i, j, pColor);
                    }
                }
            }
        }
    }
}
