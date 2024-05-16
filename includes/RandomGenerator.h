#ifndef RAY_TRACING_RANDOMGENERATOR_H
#define RAY_TRACING_RANDOMGENERATOR_H

#include <random>

#include <glm.hpp>

class RandomGenerator {
public:
    double get_random_float(double from = 0., double to = 1.);

    uint32_t get_random_uint(uint32_t to);

    glm::dvec3 get_random_sphere_vec();

    glm::dvec3 get_random_semi_sphere_vec(const glm::dvec3 &normal);

private:
    std::minstd_rand rnd_;
};

#endif //RAY_TRACING_RANDOMGENERATOR_H
