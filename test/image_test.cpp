#include "catch.hpp"
#include "image.hpp"
#include "color.hpp"

using namespace graphics;

#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE ("image can be manipulated correctly", "[image]") {
    Image img(512, 512);

    REQUIRE(img.height() == 512);
    REQUIRE(img.width() == 512);

    SECTION("Image can fill the right color") {
        img.fillcolor({0, 0, 0});
        Image imgb(512, 512);

        std::ifstream f("blackbg.json");
        {
            cereal::JSONInputArchive ar(f);
            ar(imgb);
        }
        REQUIRE(img == imgb);
    }

    SECTION("Image can create real image file correctly") {
        img.writeout("blackbg.png");
        fs::path rendered_path = "./blackbg.png";
        REQUIRE(fs::exists(rendered_path));
    }
}
