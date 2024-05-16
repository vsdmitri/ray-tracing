#ifndef HW1_ELLIPSOID_H
#define HW1_ELLIPSOID_H

#include "Object.h"

struct Ellipsoid : Object {
    Ellipsoid(glm::dvec3 rs) : rs_(rs), rs_inverse_(1./rs){}

    [[nodiscard]] ObjectIntersection intersect(Ray) override;

    [[nodiscard]] ObjectTag getTag() const override;

    [[nodiscard]] AABB getAABB() const override;

    glm::dvec3 rs_;
    glm::dvec3 rs_inverse_;
};


#endif //HW1_ELLIPSOID_H
