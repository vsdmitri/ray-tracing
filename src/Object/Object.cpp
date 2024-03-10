#include "Object.h"

void Object::prepare_ray(Ray &ray) const {
    ray.o -= position;
    fast_rotate(inverse_rotation, ray.o);
    fast_rotate(inverse_rotation, ray.dir);
}

void Object::prepare_intersection_info(ObjectIntersection &intersection, const Ray &ray) const {
    auto &normal = intersection.normal;
    intersection.is_inside = glm::dot(normal, ray.dir) > 0;
    if (intersection.is_inside) normal *= -1;
    fast_rotate(rotation, normal);
    intersection.normal = glm::normalize(normal);
}
