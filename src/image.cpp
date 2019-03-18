#include "image.hpp"
#include "raster/algorithm.hpp"
#include "raster/pointlist.hpp"
#include "color.hpp"

namespace graphics {
    void Image::setpixel(int x, int y, const RGBColor& color) {
        auto& val = rgb_.at<cv::Vec3b>(y, x);
        val.val[0] = color.b();
        val.val[1] = color.g();
        val.val[2] = color.r();
    }

    RGBColor&& Image::getpixel(int x, int y) const {
        auto& val = rgb_.at<cv::Vec3b>(y, x);
        RGBColor retval{val.val[2], val.val[1], val.val[0]};
        return std::move(retval);
    }

    void Image::fillcolor(const RGBColor& color) {
        rgb_.setTo(cv::Scalar(color.b(), color.g(), color.r()));
    }

    void Image::drawpoints(const raster::PointList &points, const RGBColor &color) {
        for (const auto& point : points.list) {
            this->setpixel(point(0), point(1), color);
        }
    }

    void Image::writeout(const char* filename) const {
        cv::imwrite(filename, rgb_);
    }

    void Image::drawline(int x1, int y1, int x2, int y2, const RGBColor& color) {
        // TODO
        // implement cropping at this level
        if (x1 < 0 || x1 >= width_ || x2 < 0 || x2 >= width_ || y1 < 0 || y1 >= height_ || y2 < 0 || y2 >= height_) {
            throw std::invalid_argument("the line contains part that's outside the image; cropping has not been implemented yet!");
        }

        if (use_antialiasing) {
            raster::XiaolinWuLine(*this, x1, y1, x2, y2, color);
        } else {
            raster::BresenhamLine(*this, x1, y1, x2, y2, color);
        }
    }

    void Image::drawcircle(int x, int y, int radius, const RGBColor& color) {
        if (x < radius || x >= width_ - radius || y < radius || y >= height_ - radius) {
            throw std::invalid_argument("the circle contains part that's outside the image; cropping has not been implemented yet!");
        }
        raster::BresenhamCircle(*this, x, y, radius, color);
    }

    void Image::drawpolygon(const raster::Polygon& polygon, const RGBColor &color) {
        raster::rasterize(*this, polygon, color);
    }
}
