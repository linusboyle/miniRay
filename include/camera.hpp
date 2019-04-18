#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"

namespace graphics {

// a orthographic perspective camera is such an object:
// a 3d-rectangle w x h and
// a viewpoint e

class Camera {
  // right-hand camera frame
  Vector3 u;
  Vector3 v;
  Vector3 w;

  coordinate_type focal_length;
  Point viewpoint;
  coordinate_type edge_length;

public:
  Camera(const Point &viewpoint, const Vector3 &view_direction,
         coordinate_type focal, coordinate_type edge);

  void setViewPoint(const Point &viewpoint);
  void setViewDirection(const Vector3 &view_direction);
  void setFocal(coordinate_type length);
  void setEdge(coordinate_type edge);

  Point source() const { return viewpoint; }
  coordinate_type edge() const { return edge_length; }

  Ray genRay(coordinate_type u_coordinate, coordinate_type v_coordinate) const;
};
} // namespace graphics

#endif /* ifndef CAMERA_HPP */
