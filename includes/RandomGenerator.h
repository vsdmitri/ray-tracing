#ifndef RAY_TRACING_RANDOMGENERATOR_H
#define RAY_TRACING_RANDOMGENERATOR_H

#include <random>

#include <glm.hpp>

class RandomGenerator {
public:
    float get_random_float();

    glm::vec3 get_random_semi_sphere_vec(const glm::vec3 &normal);
private:
    struct pcg32_random_t { uint64_t state;  uint64_t inc; };

    pcg32_random_t gen;

    static uint32_t pcg32_random_r(pcg32_random_t* rng);
};

#endif //RAY_TRACING_RANDOMGENERATOR_H
