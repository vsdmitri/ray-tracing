#ifndef HW1_OBJECT_H
#define HW1_OBJECT_H

#include <optional>

#include "gtc/quaternion.hpp"

#include "simpleStructs.h"

struct Object {
    glm::vec3 position = {0, 0, 0}, emission = {0, 0, 0};
    glm::quat rotation = {1, 0, 0, 0}, inverse_rotation = {1, 0, 0, 0};
    Color color;
    float index_of_reflection;
    Material material = Material::DIFFUSE;

    [[nodiscard]] virtual std::optional<ObjectIntersection> intersect(Ray) const = 0;

    [[nodiscard]] Ray prepare_ray(const Ray &ray) const;

    [[nodiscard]] ObjectIntersection get_intersection_info(const Ray &ray, glm::vec3 &normal, float t) const;

    virtual ~Object() = default;
};


#endif //HW1_OBJECT_H
