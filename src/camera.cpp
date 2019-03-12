#include "camera.hpp"

static const graphics::Vector3 upVector {0.0, 0.0, 1.0};

namespace graphics {
    Camera::Camera(const Point& viewpoint, const Vector3& view_direction, coordinate_type length, const ImagePlane& plane): 
        focal_length(length), 
        viewpoint(viewpoint),
        plane(plane) 
    {
        this->setViewDirection(view_direction);
    }

    void Camera::setViewPoint(const Point& viewpoint) {
        this->viewpoint = viewpoint;
    }

    void Camera::setViewDirection(const Vector3& view_direction) {
        this->w = -normalize(view_direction);
        this->u = normalize(crossProduct(upVector, w));
        this->v = crossProduct(w, u);
    }

    void Camera::setFocal(coordinate_type length) {
        this->focal_length = length;
    }

    void Camera::setPlane(const ImagePlane& plane) {
        this->plane = plane;
    }

    Ray Camera::genRay(coordinate_type u_coordinate, coordinate_type v_coordinate) const {
        Vector3 direction = focal_length * -w + u_coordinate * u + v_coordinate * v;
        return Ray(viewpoint, direction);
    }
}