#ifndef HW1_BOX_H
#define HW1_BOX_H

#include <algorithm>

#include "Object.h"
#include "algebraUtils.h"

struct Box : Object {
    Box(const glm::dvec3 s) : s(s) {}

    [[nodiscard]] std::optional<ObjectIntersection> intersect(Ray) const override;

    glm::dvec3 s;
};

#endif //HW1_BOX_H
