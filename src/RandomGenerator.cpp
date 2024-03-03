#include "RandomGenerator.h"

float RandomGenerator::get_random_float() {
    return random_gen(rnd);
}

glm::vec3 RandomGenerator::get_random_semi_sphere_vec(const glm::vec3 &normal) {
    for (;;) {
        glm::vec3 v = {random_gen(rnd, from_neg1), random_gen(rnd, from_neg1), random_gen(rnd, from_neg1)};
        float norm2 = v.x * v.x + v.y * v.y + v.z * v.z;
        if (norm2 <= 1) {
            if (glm::dot(normal, v) < 0) v *= -1;
            return v / static_cast<float>(sqrt(norm2));
        }
    }
}
