#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"

namespace graphics {
    // a orthographic perspective camera is such an object: 
    // a 3d-rectangle w x h and 
    // a viewpoint e
    
    class Camera {
        struct ImagePlane {
            coordinate_type left_bound;
            coordinate_type right_bound;
            coordinate_type top_bound;
            coordinate_type bottom_bound;
        };

        // right-hand camera frame
        Vector3 u;
        Vector3 v;
        Vector3 w;

        coordinate_type focal_length;
        Point viewpoint;
        ImagePlane plane;
    public:
        Camera(const Point& viewpoint, const Vector3& view_direction, coordinate_type length, const ImagePlane& plane);

        void setViewPoint(const Point& viewpoint);
        void setViewDirection(const Vector3& view_direction);
        void setFocal(coordinate_type length);
        void setPlane(const ImagePlane& plane);

        ImagePlane imagePlane() const {
            return plane;
        }
        Point source() const {
            return viewpoint;
        }

        Ray genRay(coordinate_type u_coordinate, coordinate_type v_coordinate) const;
    };
}

#endif /* ifndef CAMERA_HPP */
