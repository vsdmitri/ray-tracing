#ifndef HW1_OBJECT_H
#define HW1_OBJECT_H

#include <optional>

#include "gtc/quaternion.hpp"

#include "simpleStructs.h"

struct Object {
    glm::vec3 position = {0, 0, 0};
    glm::quat rotation = {1, 0, 0, 0}, inverse_rotation = {1, 0, 0, 0};
    Color color;

    virtual std::optional<float> intersect(const Ray &) = 0;

    [[nodiscard]] Ray prepare_ray(const Ray &ray) const;

    virtual ~Object() = default;
};


#endif //HW1_OBJECT_H
