#include "AABB.h"

void AABB::extend(const glm::dvec3 &p) {
    min = glm::min(min, p);
    max = glm::max(max, p);
}

void AABB::extend(const AABB &aabb) {
    min = glm::min(min, aabb.min);
    max = glm::max(max, aabb.max);
}
