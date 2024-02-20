#include "Box.h"

std::optional<ObjectIntersection> Box::intersect(Ray ray) const {
    ray = prepare_ray(ray);
    glm::vec3 ts1 = (-s - ray.o) / ray.dir;
    glm::vec3 ts2 = (+s - ray.o) / ray.dir;
    for (std::size_t i = 0; i < 3; i++)
        if (ts1[i] > ts2[i]) std::swap(ts1[i], ts2[i]);
    float t1 = max3(ts1);
    float t2 = min3(ts2);

    if (t2 < t1) return std::nullopt;

    float target_t;
    if (t1 >= 0) target_t = t1;
    else if (t2 >= 0) target_t = t2;
    else return std::nullopt;

    glm::vec3 P = ray.o + ray.dir * target_t;
    glm::vec3 current_normal = P / s;
    for (std::size_t i = 0; i < 3; i++) {
        if (std::abs(std::abs(current_normal[i]) - 1) < EPS) current_normal[i] = current_normal[i] > 0 ? 1 : -1;
        else current_normal[i] = 0;
    }

    return {get_intersection_info(ray, current_normal, target_t)};
}

