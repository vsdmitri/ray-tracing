#ifndef HW1_ELLIPSOID_H
#define HW1_ELLIPSOID_H

#include "Object.h"

struct Ellipsoid : Object {
    Ellipsoid(glm::vec3 rs) : rs(rs) {}

    std::optional<float> intersect(const Ray &ray) override;

    glm::vec3 rs;
};


#endif //HW1_ELLIPSOID_H
