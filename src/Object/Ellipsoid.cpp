#include "Ellipsoid.h"

std::optional<ObjectIntersection> Ellipsoid::intersect(Ray ray) const {
    ray = prepare_ray(ray);
    float c = glm::dot(ray.o / rs, ray.o / rs) - 1;
    float b = 2 * glm::dot(ray.o / rs, ray.dir / rs);
    float a = glm::dot(ray.dir / rs, ray.dir / rs);
    float D = b * b - 4 * a * c;
    if (D < 0) return std::nullopt;
    D = sqrt(D);

    float t1 = (-b - D) / (2 * a);
    float t2 = (-b + D) / (2 * a);

    if (t2 < t1) std::swap(t1, t2);
    float target_t;
    if (t1 >= 0) target_t = t1;
    else if (t2 >= 0) target_t = t2;
    else return std::nullopt;

    glm::vec3 P = ray.o + ray.dir * target_t;
    glm::vec3 current_normal = P / rs / rs;

    return {get_intersection_info(ray, current_normal, target_t)};
}
