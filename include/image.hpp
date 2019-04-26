#ifndef IMAGE_CPP
#define IMAGE_CPP

#include <opencv2/opencv.hpp>
#include "color.hpp"

namespace graphics {
    namespace raster {
        class PointList;

        using Polygon = PointList;
    };

    class Image {

    private:
        cv::Mat rgb_;
        int width_;
        int height_;
        bool use_antialiasing;

        bool outside(int x, int y) const;

    public:

        Image(int width, int height)
            : rgb_(height, width, CV_8UC3, cv::Scalar{0, 0, 0})
            , width_(width)
            , height_(height)
            , use_antialiasing(false)
        {}

        /*
         * color
         */
        void setpixel(int x, int y, const RGBColor& color);
        RGBColor getpixel(int x, int y) const;
        void fillcolor(const RGBColor& color); // fill color in whole image
        void fillcolor(int x, int y, const RGBColor& color); // fill color in an area

        /*
         * raster
         */
        void drawpoints(const raster::PointList& points, const RGBColor& color);
        void drawline(int x1, int y1, int x2, int y2, const RGBColor& color);
        void drawcircle(int x, int y, int radius, const RGBColor& color);
        void drawpolygon(const raster::Polygon& polygon, const RGBColor& color);

        /* image IO*/
        void writeout(const char* filename) const;
        void show() const {
            cv::imshow("intermediate picture", rgb_);
            cv::waitKey();
        }

        void setAntialiasing(bool option = true) {
            this->use_antialiasing = option;
        }

        int width() const {
            return width_;
        }

        int height() const {
            return height_;
        }

        void filter();
    };
}

#endif /* ifndef IMAGE_CPP */
