#ifndef HW1_BOX_H
#define HW1_BOX_H

#include <algorithm>

#include "Object.h"
#include "algebraUtils.h"

struct Box : Object {
    Box(const glm::dvec3 s) : s(s) {}

    [[nodiscard]] ObjectIntersection intersect(Ray) const override;

    [[nodiscard]] ObjectTag getTag() const override;

    glm::dvec3 s;
};

#endif //HW1_BOX_H
