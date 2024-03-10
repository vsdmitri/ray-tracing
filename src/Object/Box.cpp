#include "Box.h"

ObjectIntersection Box::intersect(Ray ray) const {
    prepare_ray(ray);
    glm::dvec3 ts1 = (-s - ray.o) / ray.dir;
    glm::dvec3 ts2 = (+s - ray.o) / ray.dir;
    for (std::size_t i = 0; i < 3; i++)
        if (ts1[i] > ts2[i]) std::swap(ts1[i], ts2[i]);
    double t1 = max3(ts1);
    double t2 = min3(ts2);

    if (t2 < t1) return {};

    ObjectIntersection result;

    if (t1 >= 0) {
        result.t = t1;
    } else if (t2 >= 0) {
        result.t = t2;
    } else return {};

    glm::dvec3 P = ray.o + ray.dir * result.t;
    result.normal = P / s;
    for (std::size_t i = 0; i < 3; i++) {
        if (std::abs(std::abs(result.normal[i]) - 1) < EPS) result.normal[i] = result.normal[i] > 0 ? 1 : -1;
        else result.normal[i] = 0;
    }

    prepare_intersection_info(result, ray);

    return result;
}

[[nodiscard]] ObjectTag Box::getTag() const {
    return ObjectTag::Box;
}


