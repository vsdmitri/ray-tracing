#include "AABB.h"
#include "geometryUtils.hpp"
#include "algebraUtils.h"

void AABB::extend(const glm::dvec3 &p) {
    min_ = glm::min(min_, p);
    max_ = glm::max(max_, p);
}

void AABB::extend(const AABB &aabb) {
    min_ = glm::min(min_, aabb.min_);
    max_ = glm::max(max_, aabb.max_);
}

bool AABB::intersect(const Ray &ray) const {
    const auto reverse_dir = 1.0 / ray.dir;

    auto ts1 = (min_ - ray.o) * reverse_dir;
    auto ts2 = (max_ - ray.o) * reverse_dir;

    for (std::size_t i = 0; i < 3; i++)
        if (ts1[i] > ts2[i]) std::swap(ts1[i], ts2[i]);
    double t1 = max3(ts1);
    double t2 = min3(ts2);

    if (t2 < t1) return false;
    return t2 >= 0;
}


