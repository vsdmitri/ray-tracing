#include "Ellipsoid.h"

ObjectIntersection Ellipsoid::intersect(Ray ray) {
    prepare_ray(ray);
    double c = glm::dot(ray.o * rs_inverse_, ray.o * rs_inverse_) - 1;
    double b = 2 * glm::dot(ray.o * rs_inverse_, ray.dir * rs_inverse_);
    double a = glm::dot(ray.dir * rs_inverse_, ray.dir * rs_inverse_);
    double D = b * b - 4 * a * c;
    if (D < 0) return {};
    D = sqrt(D);

    double t1 = (-b - D) / (2 * a);
    double t2 = (-b + D) / (2 * a);

    if (t2 < t1) std::swap(t1, t2);
    ObjectIntersection result;

    if (t1 >= 0) {
        result.t = t1;
    } else if (t2 >= 0) {
        result.t = t2;
    } else return {};

    glm::dvec3 P = ray.o + ray.dir * result.t;
    result.normal = P * rs_inverse_ * rs_inverse_;
    prepare_intersection_info(result, ray);
    return result;
}

ObjectTag Ellipsoid::getTag() const {
    return ObjectTag::Ellipsoid;
}

// TODO
AABB Ellipsoid::getAABB() const {
    AABB aabb;
//    aabb.extend(a);
//    aabb.extend(b);
//    aabb.extend(c);
    return aabb;
}
