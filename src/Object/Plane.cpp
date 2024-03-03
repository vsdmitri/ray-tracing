#include "Plane.h"

ObjectIntersection Plane::intersect(Ray ray) const {
    prepare_ray(ray);
    float t = -glm::dot(ray.o, normal) / glm::dot(ray.dir, normal);
    if (t < 0)
        return {};

    glm::vec3 current_normal = normal;

    return get_intersection_info(ray, current_normal, t);
}
