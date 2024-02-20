#ifndef RAY_TRACING_POINTLIGHT_H
#define RAY_TRACING_POINTLIGHT_H

#include "geometric.hpp"

#include "Light.h"

struct PointLight : Light {
    glm::vec3 position, attenuation;

    PointLight(const glm::vec3 &position) : position(position) {}

    [[nodiscard]] glm::vec3 get_intensity(const glm::vec3 &point) const override;

    [[nodiscard]] glm::vec3 get_on_light_direction(const glm::vec3 &point) const override;

    [[nodiscard]] float get_distance(const glm::vec3 &point) const override;

    void set_attenuation(const glm::vec3 &);
};


#endif //RAY_TRACING_POINTLIGHT_H
