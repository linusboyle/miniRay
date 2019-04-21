#include "random.hpp"

namespace graphics {
    RandomGenerator::RandomGenerator(typename std::minstd_rand::result_type seed, coordinate_type a, coordinate_type b) : device(seed), dist(a, b) {}

    coordinate_type RandomGenerator::next() {
        return dist(device);
    }

    void RandomGenerator::seed(std::minstd_rand::result_type s) {
        device.seed(s);
    }
}
