#include "Plane.h"

std::optional<ObjectIntersection> Plane::intersect(Ray ray) const {
    ray = prepare_ray(ray);
    double t = -glm::dot(ray.o, normal) / glm::dot(ray.dir, normal);
    if (t < 0)
        return std::nullopt;

    glm::dvec3 current_normal = normal;

    return {get_intersection_info(ray, current_normal, t)};
}
