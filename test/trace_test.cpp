#include "catch.hpp"

#include "camera.hpp"
#include "image.hpp"
#include "plane.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

using namespace graphics;

TEST_CASE("ray and object intersection computed correctly", "[ray]") {
  Surface *sphere = new Sphere(Point{0.0, 0.0, 0.0}, 1.0, {26, 188, 156});
  Ray ray(Point{1.0, 1.0, 1.0}, Vector3{-1.0, -1.0, -1.0});
  auto result =
      sphere->hit(ray, 0, std::numeric_limits<coordinate_type>::max());
  REQUIRE(result);
  REQUIRE(result.value().first - 0.42265 <
          std::numeric_limits<coordinate_type>::epsilon());
  REQUIRE(0.42265 - result.value().first >
          std::numeric_limits<coordinate_type>::epsilon());
}

//TEST_CASE("the ray tracing main function works correctly", "[ray]") {
  //Image img(512, 512);
  //img.fillcolor({255, 255, 255});

  //Scene scene;
  //scene.addObject(
      //new Sphere{Point{0.0, 0.0, 0.0}, 1.0, RGBColor{26, 188, 156}});
  //scene.addObject(new Sphere{Point{-1.9, 1.1, 0.0}, 1, RGBColor{100, 20, 35}});
  //scene.addObject(new Plane{Point{-5.0, 0.0, 0.0}, Vector3{1.0, 0.0, 0.0},
                            //RGBColor{191, 191, 191}});
  //scene.addObject(new Plane{Point{0.0, 0.0, -1.0}, Vector3{0.0, 0.0, 1.0},
                            //RGBColor{70, 70, 70}, SurfaceProperty::REFLECTIVE});
  //scene.addLightSource({Point{2.7, -0.3, 3.4}, {0.7, 0.7, 0.7}});
  //scene.addLightSource({Point{1.0, 4.3, 4.0}, {0.3, 0.3, 0.3}});
  //Camera camera(Point{5.0, 5.0, 5.0}, Vector3{-1.0, -1.0, -1.0}, 0.7, 0.4);
  //scene.render(camera, img);

  //img.show();
  //img.writeout("rendered.png");
//}

// TEST_CASE("ray tracing with triangles", "[ray]")
//{
//  Image img(512, 512);
//  img.fillcolor({ 255, 255, 255 });

//  Scene scene;
//  scene.setAmbientIntensity(0.25);
//  scene.addObject(new Triangle{ Point{ 1.0, 0.0, 0.0 },
//                                Point{ 0.0, -1.0, 0.0 },
//                                Point{ 0.0, 0.0, 1.0 },
//                                RGBColor{ 26, 188, 156 } });
//  scene.addObject(new Triangle{ Point{ 1.0, 0.0, 0.0 },
//                           Point{ 0.0, 1.0, 0.0 },
//                                Point{ 0.0, 0.0, 1.0 },
//                                RGBColor{ 26, 188, 156 } });
//  scene.addObject(new Triangle{ Point{ -1.0, 0.0, 0.0 },
//                                Point{ 0.0, -1.0, 0.0 },
//                                Point{ 0.0, 0.0, 1.0 },
//                                RGBColor{ 26, 188, 156 } });
//  scene.addObject(new Triangle{ Point{ -1.0, 0.0, 0.0 },
//                                Point{ 0.0, 1.0, 0.0 },
//                                Point{ 0.0, 0.0, 1.0 },
//                                RGBColor{ 26, 188, 156 } });
//  scene.addObject(new Plane{ Point{ 0.0, 0.0, 0.0 },
//                             Vector3{ 0.0, 0.0, 1.0 },
//                             RGBColor{ 70, 70, 70 },
//                             true });
//  scene.addLightSource({ Point{ 2.7, -0.3, 3.4 }, 0.7 });
//  scene.addLightSource({ Point{ 1.0, 4.3, 4.0 }, 0.3 });
//  Camera camera(Point{ 5.0, 5.0, 5.0 },
//                Vector3{ -1.0, -1.0, -1.0 },
//                0.7,
//                { -0.4, 0.4, 0.4, -0.4 });
//  scene.render(camera, img);

//  img.show();
//  img.writeout("triangle.png");
//}

TEST_CASE("Cornell Box", "[ray]") {
  Image img(512, 512);
  img.fillcolor({0, 0, 0});

  Scene scene;
  // scene.setAmbientIntensity({0.25, 0.25, 0.25});
  // left
  scene.addObject(new Plane{Point{0.0, 0.0, 0.0}, Vector3{0.0, 1.0, 0.0},
                            RGBColor{191, 64, 64}});
  // right
  scene.addObject(new Plane{Point{0.0, 100.0, 0.0}, Vector3{0.0, -1.0, 0.0},
                            RGBColor{64, 64, 191}});
  // front
  scene.addObject(new Plane{Point{170.0, 0.0, 0.0}, Vector3{-1.0, 0.0, 0.0},
                            RGBColor{0, 0, 0}});
  // back
  scene.addObject(new Plane{Point{0.0, 0.0, 0.0}, Vector3{1.0, 0.0, 0.0},
                            RGBColor{191, 191, 191}});
  // bottom
  scene.addObject(new Plane{Point{0.0, 0.0, 0.0}, Vector3{0.0, 0.0, 1.0},
                            RGBColor{191, 191, 191}});
  // top
  scene.addObject(new Plane{Point{0.0, 0.0, 100.0}, Vector3{0.0, 0.0, -1.0},
                            RGBColor{191, 191, 191}});
  // sphere
  scene.addObject(new Sphere{Point{27.0, 36.5, 16.5}, 16.5, RGBColor{0.99, 0.99, 0.99}, SurfaceProperty::REFLECTIVE});

  scene.addLightSource({Point{50.0, 50.0, 99.27}, RGBColor{0.7, 0.7, 0.7}});
  Camera camera(Point{75.0, 50.0, 50.0}, Vector3{-1.0, 0.0, 0.0}, 2.0, 3.0);
  scene.render(camera, img);

  img.show();
  img.writeout("cornell.png");
}
