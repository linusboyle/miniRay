#include "scene.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "shading.hpp"
#include "surface.hpp"

#include <limits>

namespace graphics {

static constexpr coordinate_type epsilon = 0.01;

Scene::~Scene() {
  for (auto ptr : objects) {
    if (ptr)
      delete ptr;
  }
}

std::optional<std::tuple<coordinate_type, Vector3, Surface *>>
Scene::getHitInfo(const Ray &ray, coordinate_type lowerbound,
                  coordinate_type upperbound) const {
  bool hit = false;
  Surface *hitObj = nullptr;
  Vector3 uNormal;
  for (auto obj : objects) {
    auto result = obj->hit(ray, lowerbound, upperbound);
    if (result) {
      hit = true;
      upperbound = result.value().first;
      uNormal = result.value().second;
      hitObj = obj;
    }
  }

  if (hit) {
    return std::tuple{upperbound, uNormal, hitObj};
  } else {
    return std::nullopt;
  }
}

bool Scene::checkHit(const Ray &ray, coordinate_type lowerbound,
                     coordinate_type upperbound) const {
  for (auto obj : objects) {
    auto result = obj->hit(ray, lowerbound, upperbound);
    if (result) {
      return true;
    }
  }
  return false;
}

RGBColor Scene::specColor(const Ray &ray, coordinate_type lowerbound,
                          coordinate_type upperbound, bool recurse) {
  auto hitResult = getHitInfo(ray, lowerbound, upperbound);

  if (hitResult) {
    coordinate_type hitPosition = std::get<0>(hitResult.value());
    Vector3 normal = std::get<1>(hitResult.value());
    Surface *hitObj = std::get<2>(hitResult.value());

    // begin shading
    Point p = ray.source() + hitPosition * ray.direction();
    RGBColor pColor = ShadingPolicy::Ambient(hitObj->color(), aIntensity);

    for (auto light : lights) {
      Vector3 lDirection = light.position - p;

      auto shadowResult = checkHit({p, lDirection}, epsilon, 1.0);

      if (!shadowResult) {
        pColor = pColor
                 // TODO:
                 // the diffuse coefficient and specualar coefficient is always
                 // the same
                 + ShadingPolicy::Lambertian(hitObj->color(), light.intensity,
                                             normal, lDirection) +
                 ShadingPolicy::BlinnPhong(hitObj->color(), light.intensity,
                                           normal, lDirection, -ray.direction(),
                                           this->phongExponent);
      }
    }

    // reflection
    if (recurse && hitObj->isReflective()) {
      Vector3 r =
          ray.direction() - 2 * scalarProduct(ray.direction(), normal) * normal;
      pColor =
          pColor + 0.2 * specColor({p, r}, epsilon,
                                   std::numeric_limits<coordinate_type>::max(),
                                   false);
    }
    return pColor;
  } else {
    return {0.0, 0.0, 0.0}; // bgcolor
  }
}

void Scene::render(const Camera &camera, Image &img) {
  auto plane = camera.imagePlane();
  const coordinate_type pWidth = plane.right_bound - plane.left_bound;
  const coordinate_type pHeight = plane.top_bound - plane.bottom_bound;

  const coordinate_type uStep = pWidth / img.width();
  const coordinate_type vStep = pHeight / img.height();

#pragma omp parallel for schedule(dynamic, 1)
  for (int i = 0; i < img.width(); ++i) {
    coordinate_type u = plane.left_bound + (i + 0.5) * uStep;
    for (int j = 0; j < img.height(); ++j) {
      if (i == 236 && j == 385) {
        std::cout << "in condition";
      }
      coordinate_type v = plane.top_bound - (j + 0.5) * vStep;
      Ray ray = camera.genRay(u, v);

      RGBColor color =
          specColor(ray, 0, std::numeric_limits<coordinate_type>::max());
      img.setpixel(i, j, color);
    }
  }
}
} // namespace graphics
