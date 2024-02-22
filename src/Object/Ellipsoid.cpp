#include "Ellipsoid.h"

std::optional<ObjectIntersection> Ellipsoid::intersect(Ray ray) const {
    ray = prepare_ray(ray);
    double c = glm::dot(ray.o / rs, ray.o / rs) - 1;
    double b = 2 * glm::dot(ray.o / rs, ray.dir / rs);
    double a = glm::dot(ray.dir / rs, ray.dir / rs);
    double D = b * b - 4 * a * c;
    if (D < 0) return std::nullopt;
    D = sqrt(D);

    double t1 = (-b - D) / (2 * a);
    double t2 = (-b + D) / (2 * a);

    if (t2 < t1) std::swap(t1, t2);
    double target_t;
    if (t1 >= 0) target_t = t1;
    else if (t2 >= 0) target_t = t2;
    else return std::nullopt;

    glm::dvec3 P = ray.o + ray.dir * target_t;
    glm::dvec3 current_normal = P / rs / rs;

    return {get_intersection_info(ray, current_normal, target_t)};
}
