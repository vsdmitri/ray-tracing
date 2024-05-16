#ifndef HW1_PLANE_H
#define HW1_PLANE_H

#include "Object.h"


struct Plane : Object {
    Plane(glm::dvec3 n) : normal_(n) {}

    [[nodiscard]] ObjectIntersection intersect(Ray) override;

    [[nodiscard]] ObjectTag getTag() const override;

    glm::dvec3 normal_;
};


#endif //HW1_PLANE_H
