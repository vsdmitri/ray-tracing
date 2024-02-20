#ifndef HW1_BOX_H
#define HW1_BOX_H

#include <algorithm>

#include "Object.h"
#include "algebraUtils.h"

struct Box : Object {
    Box(const glm::vec3 s) : s(s) {}

    std::optional<float> intersect(const Ray &ray) override;

    glm::vec3 s;
};

#endif //HW1_BOX_H
