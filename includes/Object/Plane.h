#ifndef HW1_PLANE_H
#define HW1_PLANE_H

#include "Object.h"


struct Plane : Object {
    Plane(glm::vec3 n) : normal(n) {}

    [[nodiscard]] ObjectIntersection intersect(Ray) const override;

    glm::vec3 normal;
};


#endif //HW1_PLANE_H
