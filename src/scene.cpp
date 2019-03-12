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

    RGBColor Scene::specColor(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound, bool recurse) {
        this->hitObj = nullptr;
        auto hitResult = hit(ray, lowerbound, upperbound);

        if (hitResult) {
            coordinate_type hitPosition = hitResult.value();

            // suppose the image has been filled with background color before render 
            // process, so that no trouble for that here.
        
            // begin shading
            Point p = ray.source() + hitPosition * ray.direction();
            Vector3 normal = hitObj->gradient(p);
            Surface* obj = hitObj;
            RGBColor pColor = ShadingPolicy::Ambient(hitObj->color(), aIntensity);

            for (auto light : lights) {
                Vector3 lDirection = light.position - p;

                auto shadowResult = hit({p, lDirection}, epsilon, std::numeric_limits<coordinate_type>::max());

                if (!shadowResult) {
                    pColor = pColor 
                            + ShadingPolicy::Lambertian(obj->color(), light.intensity, normal, lDirection) 
                            + ShadingPolicy::BlinnPhong(obj->color(), light.intensity, normal, lDirection, -ray.direction(), this->phongExponent);
                }
            }

            // reflection
            if (recurse && obj->isReflective()) {
                Vector3 r = ray.direction() - 2 * scalarProduct(ray.direction(), normal) * normal;
                pColor = pColor + 0.2 * specColor({p, r}, epsilon, std::numeric_limits<coordinate_type>::max(), false);
            }
            return pColor;
        } else {
            return {0.0, 0.0, 0.0};
        }          
    }

    void Scene::render(const Camera& camera, Image& img) {
        auto plane = camera.imagePlane();
        const coordinate_type pWidth = plane.right_bound - plane.left_bound;
        const coordinate_type pHeight = plane.top_bound - plane.bottom_bound;

        const coordinate_type uStep = pWidth / img.width();
        const coordinate_type vStep = pHeight / img.height();

        for (int i = 0; i < img.width(); ++i) {
            coordinate_type u = plane.left_bound + (i + 0.5) * uStep;
            for (int j = 0; j < img.height(); ++j) {
                coordinate_type v = plane.top_bound - (j + 0.5) * vStep;
                Ray ray = camera.genRay(u, v);
                
                RGBColor color = specColor(ray, 0, std::numeric_limits<coordinate_type>::max());
                img.setpixel(i, j, color);
            }
        }
    }
}
