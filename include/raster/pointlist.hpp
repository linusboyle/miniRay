#ifndef POINTLIST_HPP
#define POINTLIST_HPP

#include <vector>
#include "vector.hpp"

namespace graphics::raster {
    class PointList {
    public:
        std::vector<Point2dR> list;
        PointList& operator<<(const Point2dR&);
    };
};

#endif // POINTLIST_HPP