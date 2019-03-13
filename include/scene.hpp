#ifndef SCENE_HPP
#define SCENE_HPP 

#include "vector.hpp"
#include "color.hpp"
#include <vector>
#include <optional>

namespace graphics {
    class Camera;
    class Image;
    class Surface;
    class Ray;

    struct LightSource {
        Point position;
        coordinate_type intensity;
    };

    class Scene {
        Surface* hitObj = nullptr;

        std::vector<Surface*> objects;
        std::vector<LightSource> lights;

        coordinate_type aIntensity = 0.2;
        coordinate_type phongExponent = 10.0;

        std::optional<coordinate_type> hit(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound);
        RGBColor specColor(const Ray& ray, coordinate_type lowerbound, coordinate_type upperbound, bool recurse = true);
    public:
        void render(const Camera& camera, Image& img);
        void addObject(Surface* obj) {
            objects.push_back(obj);
        }
        void addLightSource(LightSource light) {
            lights.push_back(light);
        }
        void setAmbientIntensity(coordinate_type intensity) {
            aIntensity = intensity;
        }
        void setPhongExponent(coordinate_type exponent) {
            phongExponent = exponent;
        }

        ~Scene();
    };
}
#endif /* ifndef SCENE_HPP */
