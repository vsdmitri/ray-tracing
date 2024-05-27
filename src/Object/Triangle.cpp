#include "Triangle.h"

ObjectIntersection Triangle::intersect(Ray ray) {
    prepare_ray(ray);
    mat_[0][2] = -ray.dir.x;
    mat_[1][2] = -ray.dir.y;
    mat_[2][2] = -ray.dir.z;

    auto vec = (ray.o - a_) * glm::inverse(mat_);
    if (vec.x < 0 || vec.y < 0 || vec.x + vec.y > 1 || vec.z < 0) {
        return {};
    }

    ObjectIntersection result;
    result.t = vec.z;
    result.normal = normal_;
    prepare_intersection_info(result, ray);
    return result;
}

ObjectTag Triangle::getTag() const {
    return ObjectTag::Triangle;
}

AABB Triangle::getAABB() const {
    AABB aabb;

    aabb.extend(move_point(rotation, position, a_));
    aabb.extend(move_point(rotation, position, b_));
    aabb.extend(move_point(rotation, position, c_));
    return aabb;
}
