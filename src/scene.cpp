#include "scene.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "shading.hpp"
#include "surface.hpp"
#include "random.hpp"

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
    RGBColor pColor{0, 0, 0};
    SurfaceProperty oProperty = hitObj->property();

    switch (oProperty) {
        case SurfaceProperty::DIFFUSE: 
        {
            pColor = pColor + ShadingPolicy::Ambient(hitObj->color(), aIntensity);
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
            break;
        }
        case SurfaceProperty::REFLECTIVE:
        {
            if (recurse) {
                Vector3 r =
                    ray.direction() - 2 * scalarProduct(ray.direction(), normal) * normal;
                pColor =
                    pColor + hitObj->color() * 
                                    specColor({p, r}, epsilon,
                                    std::numeric_limits<coordinate_type>::max(),
                                    false);
            }
            break;
        }
        case SurfaceProperty::REFRACTIVE:
        default:
            break;
    }

    return pColor;
  } else {
    return {0.0, 0.0, 0.0}; // bgcolor
  }
}

void Scene::render(const Camera &camera, Image &img) {
  auto edge_width = camera.edge();

  const coordinate_type uStep = 2 * edge_width / img.width();
  const coordinate_type vStep = 2 * edge_width / img.height();

#pragma omp parallel for schedule(dynamic, 1)
  for (int i = 0; i < img.width(); ++i) {
      grand.seed(i * i);
    for (int j = 0; j < img.height(); ++j) {
        RGBColor color{0, 0, 0};
        for (int sx = 0; sx < 2; ++sx) { // subpixels
            for (int sy = 0; sy < 2; ++sy) {
                constexpr int SAMPLE = 4;
                RGBColor sColor{0, 0, 0};
                for (int sample = 0; sample < SAMPLE; ++sample) { // samples
                    coordinate_type dx = grand.next();
                    coordinate_type dy = grand.next();
                    coordinate_type u = -edge_width + (i + 0.5 * sx + 0.5 * dx) * uStep;
                    coordinate_type v = edge_width - (j + 0.5 * sy + 0.5 * dy) * vStep;
                    Ray ray = camera.genRay(u, v);
                    sColor = sColor + (1.0 / SAMPLE) * specColor(ray, 0, std::numeric_limits<coordinate_type>::max());
                }
                color = color + 0.25 * sColor;
            }
        }
        img.setpixel(i, j, color);
    }
  }
}
} // namespace graphics
