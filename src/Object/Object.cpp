#include "Object.h"

void Object::prepare_ray(Ray &ray) const {
    ray.o -= position;
    fast_rotate(inverse_rotation, ray.o);
    fast_rotate(inverse_rotation, ray.dir);
}

ObjectIntersection Object::get_intersection_info(const Ray &ray, glm::vec3 &normal, float t) const {
    bool is_inside = glm::dot(normal, ray.dir) > 0;
    if (is_inside) normal *= -1;
    fast_rotate(rotation, normal);
    return {t, glm::normalize(normal), is_inside};
}
