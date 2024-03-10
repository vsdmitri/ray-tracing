#ifndef RAY_TRACING_ELLIPSOIDDISTRIBUTION_H
#define RAY_TRACING_ELLIPSOIDDISTRIBUTION_H

#include <memory>

#include "Distribution.h"
#include "Ellipsoid.h"
#include "algebraUtils.h"

struct EllipsoidDistribution : Distribution {
    EllipsoidDistribution(std::shared_ptr<Ellipsoid> &ellipsoid) : ellipsoid_(ellipsoid) {
        rr2 = {ellipsoid_->rs.y * ellipsoid_->rs.z, ellipsoid_->rs.x * ellipsoid_->rs.z,
               ellipsoid_->rs.x * ellipsoid_->rs.y,};
    };

    glm::dvec3 sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r) const override;

    [[nodiscard]] double pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const override;

    std::shared_ptr<Ellipsoid> ellipsoid_;

    glm::dvec3 rr2;
};


#endif //RAY_TRACING_ELLIPSOIDDISTRIBUTION_H
