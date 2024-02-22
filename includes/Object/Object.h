#ifndef HW1_OBJECT_H
#define HW1_OBJECT_H

#include <optional>

#include "gtc/quaternion.hpp"

#include "simpleStructs.h"

struct Object {
    glm::dvec3 position = {0, 0, 0};
    glm::dquat rotation = {1, 0, 0, 0}, inverse_rotation = {1, 0, 0, 0};
    Color color;
    double index_of_reflection;
    Material material = Material::DIFFUSE;

    [[nodiscard]] virtual std::optional<ObjectIntersection> intersect(Ray) const = 0;

    [[nodiscard]] Ray prepare_ray(const Ray &ray) const;

    [[nodiscard]] ObjectIntersection get_intersection_info(const Ray &ray, glm::dvec3 &normal, double t) const;

    virtual ~Object() = default;
};


#endif //HW1_OBJECT_H
