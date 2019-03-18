#include "catch.hpp"
#include "image.hpp"
#include "raster/pointlist.hpp"

using namespace graphics;

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE ("image can be manipulated correctly", "[image]") {
    Image img(512, 512);

    REQUIRE(img.height() == 512);
    REQUIRE(img.width() == 512);

    SECTION("Image can fill the right color") {
        img.fillcolor({12, 109, 71});
        img.show();
    }

    SECTION("Image can create real image file correctly") {
        fs::path rendered_path_png = "./blackbg.png";
        if (fs::exists(rendered_path_png)) {
            fs::remove(rendered_path_png);
        }
        img.writeout("blackbg.png");
        REQUIRE(fs::exists(rendered_path_png));

        fs::path rendered_path_ppm= "./blackbg.ppm";
        if (fs::exists(rendered_path_ppm)) {
            fs::remove(rendered_path_ppm);
        }
        img.writeout("blackbg.ppm");
        REQUIRE(fs::exists(rendered_path_ppm));
    }

    SECTION("Image draws line correctly in all directions") {
        img.fillcolor({255, 255, 255});
        img.drawline(200, 200, 200, 100, {0, 0, 0});
        img.drawline(200, 200, 500, 450, {0, 0, 0});
        img.drawline(200, 200, 500, 10, {0, 0, 0});
        img.drawline(200, 200, 10, 500, {0, 0, 0});
        img.drawline(200, 200, 30, 10, {0, 0, 0});

        img.show();
    }

    SECTION("draw circle correctly") {
        img.fillcolor({255, 255, 255});
        img.drawcircle(200, 200, 100, {0, 0, 0});
        img.show();
    }

    SECTION("draw circle with anti aliasing correctly") {
        img.fillcolor({255, 255, 255});
        img.setAntialiasing();

        img.drawcircle(100, 100, 70, {0, 0, 0});
        img.drawcircle(240, 110, 50, {120, 90, 114});
        img.drawcircle(150, 210, 100, {240, 100, 78});

        img.show();
    }

    SECTION("Anti aliasing line drawing in all directions") {
        img.fillcolor({255, 255, 255});
        img.setAntialiasing();

        img.drawline(200, 200, 500, 450, {0, 0, 0});
        img.drawline(200, 200, 500, 10, {0, 0, 0});
        img.drawline(200, 200, 10, 500, {0, 0, 0});
        img.drawline(200, 200, 30, 10, {0, 0, 0});

        img.show();
    }

    SECTION("Anti aliasing line drawing is correct with intersection") {
        img.fillcolor({255, 255, 255});
        img.setAntialiasing();

        // a triangle
        img.drawline(90, 230, 400, 390, {0, 0, 0});
        img.drawline(20, 300, 400, 39, {0, 0, 0});
        img.drawline(300, 20, 370, 400, {0, 0, 0});

        img.show();
    }

    SECTION("polygot drawn correctly") {
        img.fillcolor({255, 255, 255});

        raster::PointList points;
        // points << Point2dR{10, 10} << Point2dR{10, 200} << Point2dR{200, 200} << Point2dR{200, 10};
        points << Point2dR{30, 10} << Point2dR{20, 300} << Point2dR{400, 300}
               << Point2dR{390, 10} << Point2dR{210, 200};

        img.drawpolygon(points, {0, 0, 0});

        img.show();
    }
}
