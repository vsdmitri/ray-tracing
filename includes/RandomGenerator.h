#ifndef RAY_TRACING_RANDOMGENERATOR_H
#define RAY_TRACING_RANDOMGENERATOR_H

#include <random>

#include <glm.hpp>

class RandomGenerator {
public:
    float get_random_float();

    glm::vec3 get_random_sphere_vec();

    glm::vec3 get_random_semi_sphere_vec(const glm::vec3 &normal);

private:
    std::minstd_rand rnd;
};

#endif //RAY_TRACING_RANDOMGENERATOR_H
