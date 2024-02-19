#include "Object.h"

Ray Object::prepare_ray(const Ray &ray) const {
    Ray new_ray = ray;
    new_ray.o -= position;
    new_ray.o = inverse_rotation * new_ray.o;
    new_ray.dir = inverse_rotation * new_ray.dir;
    new_ray.dir = glm::normalize(new_ray.dir);
    return new_ray;
}
