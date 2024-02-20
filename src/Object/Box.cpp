#include "Box.h"

std::optional<float> Box::intersect(const Ray &ray) {
    glm::vec3 ts1 = (-s - ray.o) / ray.dir;
    glm::vec3 ts2 = (+s - ray.o) / ray.dir;
    for (std::size_t i = 0; i < 3; i++)
        if (ts1[i] > ts2[i]) std::swap(ts1[i], ts2[i]);
    float t1 = max3(ts1);
    float t2 = min3(ts2);

    if (t2 < t1) return std::nullopt;

    if (t1 >= 0) return t1;
    if (t2 >= 0) return t2;

    return std::nullopt;
}

