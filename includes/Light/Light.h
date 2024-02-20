#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

#include "vec3.hpp"

#include "simpleStructs.h"

struct Light {
    glm::vec3 intensity;

    [[nodiscard]] virtual glm::vec3 get_intensity(const glm::vec3 &point) const = 0;
    [[nodiscard]] virtual glm::vec3 get_on_light_direction(const glm::vec3 &point) const = 0;
    [[nodiscard]] virtual float get_distance(const glm::vec3 &point) const = 0;

    virtual ~Light() = default;
};


#endif //RAY_TRACING_LIGHT_H
