#include "RandomGenerator.h"

float RandomGenerator::get_random_float() {
    return rnd() / 2147483647.0f;
}

glm::vec3 RandomGenerator::get_random_sphere_vec() {
    for (;;) {
        glm::vec3 v = {get_random_float() * 2 - 1, get_random_float() * 2 - 1, get_random_float() * 2 - 1};
        float norm2 = v.x * v.x + v.y * v.y + v.z * v.z;
        if (norm2 <= 1) {
            return v / static_cast<float>(sqrt(norm2));
        }
    }
}

glm::vec3 RandomGenerator::get_random_semi_sphere_vec(const glm::vec3 &normal) {
    auto v = get_random_sphere_vec();
    return v * static_cast<float>(-2 * (glm::dot(normal, v) < 0) + 1);
}

