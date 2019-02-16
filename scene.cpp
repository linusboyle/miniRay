#include "scene.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "surface.hpp"
#include "shading.hpp"

#include <limits>

static constexpr graphics::coordinate_type epsilon = 0.01;

namespace graphics {

    std::optional<coordinate_type> Scene::hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound) {
        bool hit = false;
        for (auto obj : objects) {
            auto result = obj->hit(ray, lowerbound, upperbound);
            if (result) {
                hit = true;
                upperbound = result.value();
                hitObj = obj;
            }
        }

        if (hit) {
            return upperbound;
        } else {
            return std::nullopt;
        }
    }

    void Scene::render(const Camera& camera, Image& img) {
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
                
                this->hitObj = nullptr;
                auto hitResult = hit(ray, 0, std::numeric_limits<coordinate_type>::max());
                if (hitResult) {
                    coordinate_type hitPosition = hitResult.value();

                    // suppose the image has been filled with background color before render 
                    // process, so that no trouble for that here.
                
                    // begin shading
                    Point p = ray.source() + hitPosition * ray.direction();
                    Vector3 normal = hitObj->gradient(p);
                    RGBColor pColor = ShadingPolicy::Ambient(hitObj->color(), aIntensity);
                    Surface* obj = hitObj;

                    for (auto light : lights) {
                        Vector3 lDirection = light.position - p;

                        auto shadowResult = hit({p, lDirection}, epsilon, std::numeric_limits<coordinate_type>::max());

                        if (!shadowResult) {
                            pColor = pColor 
                                   + ShadingPolicy::Lambertian(obj->color(), light.intensity, normal, lDirection) 
                                   + ShadingPolicy::BlinnPhong(obj->color(), light.intensity, normal, lDirection, -ray.direction(), this->phongExponent);                    
                        }
                    }

                    img.setpixel(i, j, pColor);
                }
            }
        }
    }
}
