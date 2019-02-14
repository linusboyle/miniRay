#ifndef SCENE_HPP
#define SCENE_HPP 

#include <vector>
#include "vector.hpp"

namespace graphics {
    class Camera;
    class Image;
    class Surface;

    struct LightSource {
        Point position;
        coordinate_type intensity;
    };

    class Scene {
        std::vector<Surface*> objects;
        std::vector<LightSource> lights;
    public:
        void render(const Camera& camera, Image& img) const;
        void addObject(Surface* obj) {
            objects.push_back(obj);
        }
        void addLightSource(LightSource light) {
            lights.push_back(light);
        }
    };
}
#endif /* ifndef SCENE_HPP */
