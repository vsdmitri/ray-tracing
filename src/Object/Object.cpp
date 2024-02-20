#include "Object.h"

Ray Object::prepare_ray(const Ray &ray) const {
    Ray new_ray = ray;
    new_ray.o -= position;
    new_ray.o = inverse_rotation * new_ray.o;
    new_ray.dir = inverse_rotation * new_ray.dir;
    new_ray.dir = glm::normalize(new_ray.dir);
    return new_ray;
}

ObjectIntersection Object::get_intersection_info(const Ray &ray, glm::vec3 &normal, float t) const {
    bool is_inside = glm::dot(normal, ray.dir) > 0;
    if (is_inside) normal *= -1;
    normal = rotation * normal;
    return {t, glm::normalize(normal), is_inside};
}
