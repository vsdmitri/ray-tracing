#include "Plane.h"

ObjectIntersection Plane::intersect(Ray ray) const {
    prepare_ray(ray);
    double t = -glm::dot(ray.o, normal) / glm::dot(ray.dir, normal);
    if (t < 0)
        return {};

    ObjectIntersection result;
    result.t = t;
    result.normal = normal;
    prepare_intersection_info(result, ray);
    return result;
}

ObjectTag Plane::getTag() const {
    return ObjectTag::Plane;
}
