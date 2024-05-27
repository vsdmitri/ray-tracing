#include "Box.h"

ObjectIntersection Box::intersect(Ray ray) {
    prepare_ray(ray);
    auto inverse_dir = 1. / ray.dir;
    glm::dvec3 ts1 = (-s_ - ray.o) * inverse_dir;
    glm::dvec3 ts2 = (+s_ - ray.o) * inverse_dir;
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
    result.normal = P * s_inverse_;
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

AABB Box::getAABB() const {
    AABB aabb;
    for (int x: {-1, 1}) {
        for (int y: {-1, 1}) {
            for (int z: {-1, 1}) {
                aabb.extend(move_point(rotation, position, s_ * glm::dvec3{x, y, z}));
            }
        }
    }
    return aabb;
}


