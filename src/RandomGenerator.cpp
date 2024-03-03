#include "RandomGenerator.h"

uint32_t RandomGenerator::pcg32_random_r(RandomGenerator::pcg32_random_t *rng) {
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}


float RandomGenerator::get_random_float() {
    return (RandomGenerator::pcg32_random_r(&gen) >> 8) / static_cast<float> (1 << 24);
}

glm::vec3 RandomGenerator::get_random_semi_sphere_vec(const glm::vec3 &normal) {
    for (;;) {
        glm::vec3 v = {get_random_float() * 2 - 1, get_random_float() * 2 - 1, get_random_float() * 2 - 1};
        float norm2 = v.x * v.x + v.y * v.y + v.z * v.z;
        if (norm2 <= 1) {
            if (glm::dot(normal, v) < 0) v *= -1;
            return v / static_cast<float>(sqrt(norm2));
        }
    }
}
