#include <chrono>

#include "RandomGenerator.h"

RandomGenerator::RandomGenerator() : rnd_(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {

}

double RandomGenerator::get_random_float(double from, double to) {
    return (to - from) * rnd_() / 2147483647.0 + from;
}

uint32_t RandomGenerator::get_random_uint(uint32_t to) {
    return rnd_() % to;
}

glm::dvec3 RandomGenerator::get_random_sphere_vec() {
    for (;;) {
        glm::dvec3 v = {get_random_float(-1, 1), get_random_float(-1, 1), get_random_float(-1, 1)};
        double norm2 = v.x * v.x + v.y * v.y + v.z * v.z;
        if (norm2 <= 1) {
            return v / static_cast<double>(sqrt(norm2));
        }
    }
}

glm::dvec3 RandomGenerator::get_random_semi_sphere_vec(const glm::dvec3 &normal) {
    auto v = get_random_sphere_vec();
    return v * static_cast<double>(-2 * (glm::dot(normal, v) < 0) + 1);
}


