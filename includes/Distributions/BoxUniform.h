#ifndef RAY_TRACING_BOXUNIFORM_H
#define RAY_TRACING_BOXUNIFORM_H

#include <memory>

#include "Distribution.h"
#include "Box.h"

struct BoxUniform : Distribution {
    BoxUniform(std::shared_ptr<Box> &box) : box_(box) {
        w_ = 4. * glm::dvec3{box->s_.y * box->s_.z, box->s_.x * box->s_.z, box->s_.x * box->s_.y};
        area_ = 2 * (w_.x + w_.y + w_.z);
        area_inverse_ = 1. / area_;
    };

    glm::dvec3 sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r, bool regen = false) const override;

    [[nodiscard]] double pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const override;

    std::shared_ptr<Box> box_;
    glm::dvec3 w_;
    double area_;
    double area_inverse_;
};


#endif //RAY_TRACING_BOXUNIFORM_H
