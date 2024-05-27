#ifndef RAY_TRACING_AABB_H
#define RAY_TRACING_AABB_H

#include <glm.hpp>

#include "simpleStructs.h"

struct AABB {
    void extend(const glm::dvec3 &p);

    void extend(const AABB &aabb);

    [[nodiscard]] bool intersect(const Ray &r) const;


    glm::dvec3 min_ = {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                       std::numeric_limits<double>::max()};
    glm::dvec3 max_ = -min_;
};


#endif //RAY_TRACING_AABB_H
