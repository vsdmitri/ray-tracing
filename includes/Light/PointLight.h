#ifndef RAY_TRACING_POINTLIGHT_H
#define RAY_TRACING_POINTLIGHT_H

#include "geometric.hpp"

#include "Light.h"

struct PointLight : Light {
    glm::dvec3 position, attenuation;

    PointLight(const glm::dvec3 &position) : position(position) {}

    [[nodiscard]] glm::dvec3 get_intensity(const glm::dvec3 &point) const override;

    [[nodiscard]] glm::dvec3 get_on_light_direction(const glm::dvec3 &point) const override;

    [[nodiscard]] double get_distance(const glm::dvec3 &point) const override;

    void set_attenuation(const glm::dvec3 &);
};


#endif //RAY_TRACING_POINTLIGHT_H
