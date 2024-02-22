#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

#include "vec3.hpp"

#include "simpleStructs.h"

struct Light {
    glm::dvec3 intensity;

    [[nodiscard]] virtual glm::dvec3 get_intensity(const glm::dvec3 &point) const = 0;
    [[nodiscard]] virtual glm::dvec3 get_on_light_direction(const glm::dvec3 &point) const = 0;
    [[nodiscard]] virtual double get_distance(const glm::dvec3 &point) const = 0;

    virtual ~Light() = default;
};


#endif //RAY_TRACING_LIGHT_H
