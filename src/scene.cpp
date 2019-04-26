#include "scene.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "shading.hpp"
#include "surface.hpp"
#include "random.hpp"

#include <limits>

namespace graphics {

//static constexpr coordinate_type epsilon = 0.01;

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

//bool Scene::checkHit(const Ray &ray, coordinate_type lowerbound,
                     //coordinate_type upperbound) const {
  //for (auto obj : objects) {
    //auto result = obj->hit(ray, lowerbound, upperbound);
    //if (result) {
      //return true;
    //}
  //}
  //return false;
//}

RGBColor Scene::specColor(const Ray &ray, uint8_t depth) {
  auto hitResult = getHitInfo(ray, 0.0, std::numeric_limits<coordinate_type>::max());

  if (hitResult) {
    Surface *hitObj = std::get<2>(hitResult.value());
    RGBColor color = hitObj->color();
    coordinate_type maxrefl = color.maxc();

    if (++depth > 4) {
        if (grand.next() < maxrefl) {
            color = (1 / maxrefl) * color;
        } else {
            return hitObj->emission();
        }
    }

    coordinate_type para = std::get<0>(hitResult.value());
    Vector3 normal = std::get<1>(hitResult.value());
    Point pos = ray.source() + para * ray.direction();
    SurfaceProperty prop = hitObj->property();

    switch (prop) {
        case SurfaceProperty::DIFFUSE: 
        {
            coordinate_type r1 = 2 * M_PI * grand.next();
            coordinate_type r2 = grand.next();
            coordinate_type r2s = std::sqrt(r2);
            Vector3 u = normalize(crossProduct(std::fabs(normal(0)) > 0.1 ? Vector3{0.0, 1.0, 0.0} : Vector3{1.0, 0.0, 0.0}, normal));
            Vector3 v = crossProduct(normal, u);
            Vector3 newdir = normalize(r2s * std::cos(r1) * u + r2s * std::sin(r1) * v + std::sqrt(1 - r2) * normal); 

            return hitObj->emission() + color * specColor(Ray{pos, newdir}, depth);
            //pColor = pColor + ShadingPolicy::Ambient(hitObj->color(), aIntensity);
            //for (auto light : lights) {
                //Vector3 lDirection = light.position - p;

                //auto shadowResult = checkHit({p, lDirection}, epsilon, 1.0);

                //if (!shadowResult) {
                    //pColor = pColor
                            //// TODO:
                            //// the diffuse coefficient and specualar coefficient is always
                            //// the same
                            //+ ShadingPolicy::Lambertian(hitObj->color(), light.intensity,
                                                        //normal, lDirection) +
                            //ShadingPolicy::BlinnPhong(hitObj->color(), light.intensity,
                                                    //normal, lDirection, -ray.direction(),
                                                    //this->phongExponent);
                //}
            //}
            break;
        }
        case SurfaceProperty::REFLECTIVE:
        {
            Vector3 r =
                ray.direction() - 2 * scalarProduct(ray.direction(), normal) * normal;
            return hitObj->emission() + color * specColor({pos, r}, depth);
            //if (recurse) {
                //pColor =
                    //pColor + hitObj->color() * 
                                    //specColor({p, r}, epsilon,
                                    //std::numeric_limits<coordinate_type>::max(),
                                    //false);
            //}
            break;
        }
        case SurfaceProperty::REFRACTIVE:
        default:
            break;
    }
  }
  return {0.0, 0.0, 0.0}; // bgcolor
}

void Scene::render(const Camera &camera, Image &img, uint32_t sampleCon) {
  coordinate_type edge_width = camera.edge();
  coordinate_type edge_height = edge_width / img.width() * img.height();

  const coordinate_type uStep = 2 * edge_width / img.width();
  const coordinate_type vStep = uStep;

#pragma omp parallel for schedule(dynamic, 1)
  for (int i = 0; i < img.width(); ++i) {
    grand.seed(i * i);
    std::fprintf(stderr, "\rRendering (%d spp) %5.2f%%", sampleCon * 4, i * 100.0 / (img.width() - 1));
    for (int j = 0; j < img.height(); ++j) {
        RGBColor color{0, 0, 0};
        for (int sx = 0; sx < 2; ++sx) { // subpixels
            for (int sy = 0; sy < 2; ++sy) {
                RGBColor sampleApprox{0, 0, 0};
                for (uint32_t sample = 0; sample < sampleCon; ++sample) { // samples
                    coordinate_type dx = grand.next();
                    coordinate_type dy = grand.next();
                    coordinate_type u = -edge_width + (i + 0.5 * sx + 0.5 * dx) * uStep;
                    coordinate_type v = edge_height - (j + 0.5 * sy + 0.5 * dy) * vStep;
                    Ray ray = camera.genRay(u, v);
                    sampleApprox = sampleApprox + (1.0 / sampleCon) * specColor(ray, 0);
                }
                color = color + 0.25 * sampleApprox;
            }
        }
        img.setpixel(i, j, color);
    }
  }
}
} // namespace graphics
