#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "Object.h"

struct Triangle : Object {
    Triangle(const glm::dvec3 &a, const glm::dvec3 &b, const glm::dvec3 &c) : a_(a), b_(b), c_(c),
                                                                              normal_(glm::cross(b - a, c - a)) {
        mat_[0][0] = (b - a).x;
        mat_[1][0] = (b - a).y;
        mat_[2][0] = (b - a).z;

        mat_[0][1] = (c - a).x;
        mat_[1][1] = (c - a).y;
        mat_[2][1] = (c - a).z;
    }

    [[nodiscard]] ObjectIntersection intersect(Ray) override;

    [[nodiscard]] ObjectTag getTag() const override;

    [[nodiscard]] AABB getAABB() const override;


    glm::dvec3 a_, b_, c_, normal_;
    glm::dmat3x3 mat_;
    AABB aabb_;
};


#endif //RAY_TRACING_TRIANGLE_H
