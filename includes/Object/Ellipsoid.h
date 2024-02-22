#ifndef HW1_ELLIPSOID_H
#define HW1_ELLIPSOID_H

#include "Object.h"

struct Ellipsoid : Object {
    Ellipsoid(glm::dvec3 rs) : rs(rs) {}

    [[nodiscard]] std::optional<ObjectIntersection> intersect(Ray) const override;

    glm::dvec3 rs;
};


#endif //HW1_ELLIPSOID_H
