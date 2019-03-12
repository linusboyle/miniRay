#include "catch.hpp"
#include "image.hpp"
#include "color.hpp"

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
        img.writeout("blackbg.png");
        fs::path rendered_path_png = "./blackbg.png";
        REQUIRE(fs::exists(rendered_path_png));

        img.writeout("blackbg.ppm");
        fs::path rendered_path_ppm= "./blackbg.png";
        REQUIRE(fs::exists(rendered_path_ppm));
    }

    SECTION("Image draws line correctly in all directions") {
        img.fillcolor({255, 255, 255});
        img.drawline(200, 200, 500, 450, {0, 0, 0});
        img.drawline(200, 200, 500, 10, {0, 0, 0});
        img.drawline(200, 200, 10, 500, {0, 0, 0});
        img.drawline(200, 200, 30, 10, {0, 0, 0});

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
}
