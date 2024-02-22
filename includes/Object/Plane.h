#ifndef HW1_PLANE_H
#define HW1_PLANE_H

#include "Object.h"


struct Plane : Object {
    Plane(glm::dvec3 n) : normal(n) {}

    [[nodiscard]] std::optional<ObjectIntersection> intersect(Ray) const override;

    glm::dvec3 normal;
};


#endif //HW1_PLANE_H
