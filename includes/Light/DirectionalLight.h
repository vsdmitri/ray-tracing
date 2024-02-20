#ifndef RAY_TRACING_DIRECTIONALLIGHT_H
#define RAY_TRACING_DIRECTIONALLIGHT_H

#include "Light.h"

struct DirectionalLight : Light {
    glm::vec3 direction;

    DirectionalLight(const glm::vec3& direction) : direction(direction) {}

    [[nodiscard]] glm::vec3 get_intensity(const glm::vec3 &point) const override;
    [[nodiscard]] glm::vec3 get_on_light_direction(const glm::vec3 &point) const override;
    [[nodiscard]] float get_distance(const glm::vec3 &point) const override;
};


#endif //RAY_TRACING_DIRECTIONALLIGHT_H
