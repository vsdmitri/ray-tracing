#include "Plane.h"

ObjectIntersection Plane::intersect(Ray ray) {
    prepare_ray(ray);
    double t = -glm::dot(ray.o, normal_) / glm::dot(ray.dir, normal_);
    if (t < 0)
        return {};

    ObjectIntersection result;
    result.t = t;
    result.normal = normal_;
    prepare_intersection_info(result, ray);
    return result;
}

ObjectTag Plane::getTag() const {
    return ObjectTag::Plane;
}
