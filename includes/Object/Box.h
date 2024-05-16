#ifndef HW1_BOX_H
#define HW1_BOX_H

#include <algorithm>

#include "Object.h"
#include "algebraUtils.h"

struct Box : Object {
    Box(const glm::dvec3 s) : s_(s), s_inverse_(1.0/ s) {}

    [[nodiscard]] ObjectIntersection intersect(Ray) override;

    [[nodiscard]] ObjectTag getTag() const override;

    [[nodiscard]] AABB getAABB() const override;

    glm::dvec3 s_;
    glm::dvec3 s_inverse_;
};

#endif //HW1_BOX_H
