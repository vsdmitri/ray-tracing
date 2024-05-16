#ifndef RAY_TRACING_AABB_H
#define RAY_TRACING_AABB_H

#include <glm.hpp>

struct AABB {
    glm::dvec3 min = {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                      std::numeric_limits<double>::max()};
    glm::dvec3 max = {std::numeric_limits<double>::min(), std::numeric_limits<double>::min(),
                      std::numeric_limits<double>::min()};

    void extend(const glm::dvec3 &p);

    void extend(const AABB &aabb);
};


#endif //RAY_TRACING_AABB_H
