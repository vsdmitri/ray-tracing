#ifndef RAY_TRACING_ELLIPSOIDDISTRIBUTION_H
#define RAY_TRACING_ELLIPSOIDDISTRIBUTION_H

#include <memory>

#include "Distribution.h"
#include "Ellipsoid.h"
#include "algebraUtils.h"

struct EllipsoidDistribution : Distribution {
    EllipsoidDistribution(std::shared_ptr<Ellipsoid> &ellipsoid) : ellipsoid_(ellipsoid) {
        rr2_ = {ellipsoid_->rs_.y * ellipsoid_->rs_.z, ellipsoid_->rs_.x * ellipsoid_->rs_.z,
               ellipsoid_->rs_.x * ellipsoid_->rs_.y,};
        rr2_ *= rr2_;
    };

    glm::dvec3 sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r, bool regen = true) const override;

    [[nodiscard]] double pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const override;

    std::shared_ptr<Ellipsoid> ellipsoid_;

    glm::dvec3 rr2_;
};


#endif //RAY_TRACING_ELLIPSOIDDISTRIBUTION_H
