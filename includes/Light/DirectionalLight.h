#ifndef RAY_TRACING_DIRECTIONALLIGHT_H
#define RAY_TRACING_DIRECTIONALLIGHT_H

#include "Light.h"

struct DirectionalLight : Light {
    glm::dvec3 direction;

    DirectionalLight(const glm::dvec3& direction) : direction(direction) {}

    [[nodiscard]] glm::dvec3 get_intensity(const glm::dvec3 &point) const override;
    [[nodiscard]] glm::dvec3 get_on_light_direction(const glm::dvec3 &point) const override;
    [[nodiscard]] double get_distance(const glm::dvec3 &point) const override;
};


#endif //RAY_TRACING_DIRECTIONALLIGHT_H
