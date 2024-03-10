#ifndef RAY_TRACING_COSINE_H
#define RAY_TRACING_COSINE_H

#include "Distribution.h"

struct Cosine : Distribution {
    glm::dvec3 sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r, bool regen = false) const override;

    [[nodiscard]] double pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const override;
};


#endif //RAY_TRACING_COSINE_H
