#include "raster/pointlist.hpp"

namespace graphics::raster {
    PointList& PointList::operator<<(const Point2dR& point) {
        list.push_back(point);
        return *this;
    }
};