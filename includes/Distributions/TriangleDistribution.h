#ifndef RAY_TRACING_TRIANGLEDISTRIBUTION_H
#define RAY_TRACING_TRIANGLEDISTRIBUTION_H


#include <memory>

#include "Distribution.h"
#include "Triangle.h"

struct TriangleDistribution : Distribution {
    TriangleDistribution(std::shared_ptr<Triangle> &triangle) : triangle_(triangle) {
        area_ = 0.5 * glm::length(triangle->normal_);
    };

    glm::dvec3 sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r, bool regen = false) const override;

    [[nodiscard]] double pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const override;

    std::shared_ptr<Triangle> triangle_;
    double area_;
};


#endif //RAY_TRACING_TRIANGLEDISTRIBUTION_H
