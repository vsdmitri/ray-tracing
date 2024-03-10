#ifndef RAY_TRACING_DISTRIBUTION_H
#define RAY_TRACING_DISTRIBUTION_H

#include <glm.hpp>

#include "RandomGenerator.h"
#include "simpleStructs.h"

struct Distribution {
    virtual glm::dvec3 sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator & r, bool regen = false) const = 0;

    [[nodiscard]] virtual double pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const = 0;

    double get_p_factor(const glm::dvec3& x, const glm::dvec3& y, const glm::dvec3& n) const;

    virtual ~Distribution() = default;
};

#endif //RAY_TRACING_DISTRIBUTION_H
