#ifndef SCENE_HPP
#define SCENE_HPP 

#include <vector>

namespace graphics {
    class Camera;
    class Image;
    class Surface;

    class Scene {
        std::vector<Surface*> objects;
    public:
        void render(const Camera& camera, const Image& img) const;
        void addObject(Surface* obj) {
            objects.push_back(obj);
        }
    };
}
#endif /* ifndef SCENE_HPP */
