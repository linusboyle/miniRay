#ifndef SCENE_HPP
#define SCENE_HPP

#include "color.hpp"
#include "random.hpp"
#include <optional>
#include <vector>

namespace graphics {
class Camera;
class Image;
class Surface;
class Ray;

struct LightSource {
  Point position;
  RGBColor intensity;
};

class Scene {
    RandomGenerator grand{0, 0.0, 1.0};
  std::vector<Surface *> objects;
  std::vector<LightSource> lights;

  RGBColor aIntensity{0.1, 0.1, 0.1};
  coordinate_type phongExponent = 8.0;

  bool checkHit(const Ray &ray, coordinate_type lowerbound,
                coordinate_type upperbound) const;

  std::optional<std::tuple<coordinate_type, Vector3, Surface *>>
  getHitInfo(const Ray &ray, coordinate_type lowerbound,
             coordinate_type upperbound) const;

  RGBColor specColor(const Ray &ray, coordinate_type lowerbound,
                     coordinate_type upperbound, bool recurse = true);

public:
  void render(const Camera &camera, Image &img);
  void addObject(Surface *obj) { objects.push_back(obj); }
  void addLightSource(LightSource light) { lights.push_back(light); }
  void setAmbientIntensity(RGBColor intensity) { aIntensity = intensity; }
  void setPhongExponent(coordinate_type exponent) { phongExponent = exponent; }

  ~Scene();
};
} // namespace graphics
#endif /* ifndef SCENE_HPP */
