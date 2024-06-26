#ifndef RAY_TRACING_MIXDISTRIBUTION_H
#define RAY_TRACING_MIXDISTRIBUTION_H

#include <memory>

#include "Distribution.h"

struct MixDistribution : Distribution {
    MixDistribution(std::vector<std::unique_ptr<Distribution>> &&dists) : dists_(std::move(dists)) {
        assert(!dists_.empty());
    }

    glm::dvec3 sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r, bool regen = true) const override;

    [[nodiscard]] double pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const override;

    std::vector<std::unique_ptr<Distribution>> dists_;

    mutable uint32_t last_id_;
};


#endif //RAY_TRACING_MIXDISTRIBUTION_H
