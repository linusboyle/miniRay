#include "catch.hpp"
#include "image.hpp"
#include "color.hpp"

using namespace graphics;

#include <fstream>
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"

TEST_CASE ("image can be manipulated correctly", "[image]") {
    Image img(Width{512}, Height{512});

    REQUIRE(img.height() == 512);
    REQUIRE(img.width() == 512);

    img.fillcolor({0, 0, 0});
    img.writeout("blackbg.png");

    std::ofstream f("blackbg.json");
    {
        cereal::JSONOutputArchive ar(f);
        ar(img);
    }
}
