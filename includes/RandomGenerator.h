#ifndef RAY_TRACING_RANDOMGENERATOR_H
#define RAY_TRACING_RANDOMGENERATOR_H

#include <random>

#include <glm.hpp>

class RandomGenerator {
public:
    float get_random_float();

    glm::vec3 get_random_semi_sphere_vec(const glm::vec3 &normal);
private:
    std::random_device rnd;
    std::uniform_real_distribution<float>::param_type from_neg1{-1, 1};
    std::uniform_real_distribution<float> random_gen;
};

#endif //RAY_TRACING_RANDOMGENERATOR_H
