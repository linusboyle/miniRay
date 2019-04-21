#ifndef RANDOM_GENERATER_HPP
#define RANDOM_GENERATER_HPP

#include <random>
#include "type.hpp"

namespace graphics {
    class RandomGenerator {
         std::minstd_rand device;
         std::uniform_real_distribution<coordinate_type> dist;
    public:
        RandomGenerator(typename std::minstd_rand::result_type seed, coordinate_type a, coordinate_type b);
        coordinate_type next();
        void seed(typename std::minstd_rand::result_type s);
    };
}
#endif
