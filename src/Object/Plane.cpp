#include "Plane.h"

std::optional<float> Plane::intersect(const Ray &ray) {
    float t = -glm::dot(ray.o, normal) / glm::dot(ray.dir, normal);
    if (t < 0)
        return std::nullopt;
    else
        return t;
}
