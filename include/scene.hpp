#ifndef SCENE_HPP
#define SCENE_HPP

#include "color.hpp"
#include "vector.hpp"
#include <optional>
#include <vector>

namespace graphics {
class Camera;
class Image;
class Surface;
class Ray;

struct LightSource
{
  Point position;
  coordinate_type intensity;
};

class Scene
{
  std::vector<Surface*> objects;
  std::vector<LightSource> lights;

  coordinate_type aIntensity = 0.2;
  coordinate_type phongExponent = 10.0;

  bool checkHit(const Ray& ray,
                coordinate_type lowerbound,
                coordinate_type upperbound) const;

  std::optional<std::tuple<coordinate_type, Vector3, Surface*>> getHitInfo(
    const Ray& ray,
    coordinate_type lowerbound,
    coordinate_type upperbound) const;

  RGBColor specColor(const Ray& ray,
                     coordinate_type lowerbound,
                     coordinate_type upperbound,
                     bool recurse = true);

public:
  void render(const Camera& camera, Image& img);
  void addObject(Surface* obj) { objects.push_back(obj); }
  void addLightSource(LightSource light) { lights.push_back(light); }
  void setAmbientIntensity(coordinate_type intensity)
  {
    aIntensity = intensity;
  }
  void setPhongExponent(coordinate_type exponent) { phongExponent = exponent; }

  ~Scene();
};
}
#endif /* ifndef SCENE_HPP */
