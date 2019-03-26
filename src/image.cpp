#include "image.hpp"
#include "raster/algorithm.hpp"
#include "raster/pointlist.hpp"
#include <queue>

namespace graphics {
    bool Image::outside(int x, int y) const {
        if (x < 0 || x >= this->width_ || y < 0 || y >= this->height_) {
            return true;
        }

        return false;
    }

    void Image::setpixel(int x, int y, const RGBColor& color) {
        auto& val = rgb_.at<cv::Vec3b>(y, x);
        val.val[0] = color.b();
        val.val[1] = color.g();
        val.val[2] = color.r();
    }

    RGBColor Image::getpixel(int x, int y) const {
        auto& val = rgb_.at<cv::Vec3b>(y, x);
        RGBColor retval{val.val[2], val.val[1], val.val[0]};
        return retval;
    }

    void Image::fillcolor(const RGBColor& color) {
        rgb_.setTo(cv::Scalar(color.b(), color.g(), color.r()));
    }

    void Image::fillcolor(int x, int y, const RGBColor& fgcolor) {
        if (outside(x, y)) {
            throw std::invalid_argument("the point is outside the image!");
        }

        RGBColor&& bgcolor = getpixel(x, y);

        std::queue<std::pair<int, int>> q;
        q.push({x, y});

        cv::Mat_<bool> inqueue(this->width_, this->height_, false);
        inqueue(y, x) = true;

        while (!q.empty()) {
            std::pair<int, int> point = q.front();
            q.pop();

            int px = point.first;
            int py = point.second;

            if (!outside(px, py) && getpixel(px, py) == bgcolor) {
                setpixel(px, py, fgcolor);

                // expand
                if (!inqueue(px + 1, py)) {
                    q.push({px + 1, py});
                    inqueue(px + 1, py) = true;
                }
                if (!inqueue(px - 1, py)) {
                    q.push({px - 1, py});
                    inqueue(px - 1, py) = true;
                }
                if (!inqueue(px, py + 1)) {
                    q.push({px, py + 1});
                    inqueue(px, py + 1) = true;
                }
                if (!inqueue(px, py - 1)) {
                    q.push({px, py - 1});
                    inqueue(px, py - 1) = true;
                }
            }
        }
    }

    void Image::drawpoints(const raster::PointList &points, const RGBColor &color) {
        for (const auto& point : points.list) {
            int x = point(0);
            int y = point(1);

            if (outside(x, y)) {
                throw std::invalid_argument("some point of polygon is outside the image");
            }
            this->setpixel(x, y, color);
        }
    }

    void Image::writeout(const char* filename) const {
        cv::imwrite(filename, rgb_);
    }

    void Image::drawline(int x1, int y1, int x2, int y2, const RGBColor& color) {
        // TODO
        // implement cropping at this level
        if (outside(x1, y1) || outside(x2, y2)) {
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

        if (use_antialiasing) {
            raster::XiaolinWuCircle(*this, x, y, radius, color);
        } else {
            raster::BresenhamCircle(*this, x, y, radius, color);
        }
    }

    void Image::drawpolygon(const raster::Polygon& polygon, const RGBColor &color) {
        raster::rasterize(*this, polygon, color);
    }

    void Image::filter() {
        cv::Mat dist;

        cv::Mat kernel = (cv::Mat_<double>(3, 3) << 1/16.0, 2/16.0, 1/16.0,
                                                    2/16.0, 4/16.0, 2/16.0,
                                                    1/16.0, 2/16.0, 1/16.0);

        cv::filter2D(rgb_, dist, -1, kernel);

        rgb_ = dist;
    }
}